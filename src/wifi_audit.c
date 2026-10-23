#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <arpa/inet.h>
#include "wifi_audit.h"
#include "exporter.h"

static const char *g_wifi_output = NULL;

struct ieee80211_header {
    uint8_t frame_control;
    uint8_t flags;
    uint16_t duration;
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint16_t sequence_control;
};

void packet_handler(u_char *user_args, const struct pcap_pkthdr *header, const u_char *packet) {
    (void)user_args;

    if (header->caplen < 36) return;

    struct ieee80211_header *wifi_hdr = (struct ieee80211_header *)packet;

    if (wifi_hdr->frame_control == 0x80) { // Beacon Frame
        unsigned char *bssid = wifi_hdr->addr3;
        int offset = 24 + 12;
        char ssid[33] = {0};
        int channel = -1;
        char security[32] = "Open / WEP";

        while (offset < (int)header->caplen) {
            uint8_t tag_number = packet[offset];
            uint8_t tag_length = packet[offset + 1];

            if (offset + 2 + tag_length > header->caplen) break;

            if (tag_number == 0) {
                if (tag_length > 0 && tag_length < 32) {
                    memcpy(ssid, &packet[offset + 2], tag_length);
                    ssid[tag_length] = '\0';
                } else {
                    strcpy(ssid, "<Hidden SSID>");
                }
            }

            if (tag_number == 3 && tag_length == 1) {
                channel = packet[offset + 2];
            }

            if (tag_number == 48) {
                int rsn_end = offset + 2 + tag_length;
                int has_sae = 0;
                if (tag_length >= 16) {
                    for (int i = offset + 2 + 8; i < rsn_end - 3; i++) {
                        if (packet[i] == 0x00 && packet[i+1] == 0x0F && packet[i+2] == 0xAC && packet[i+3] == 0x08) {
                            has_sae = 1;
                            break;
                        }
                    }
                }
                if (has_sae) {
                    strcpy(security, "WPA3-Personal (SAE)");
                } else {
                    strcpy(security, "WPA2-AES");
                }
            }

            offset += 2 + tag_length;
        }

        printf("[BANKAI Wi-Fi] BSSID: %02X:%02X:%02X:%02X:%02X:%02X | Canal: %-2d | Sec: %-20s | SSID: %s\n",
               bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5],
               channel, security, (strlen(ssid) > 0) ? ssid : "<Hidden>");

        bankai_export_json(g_wifi_output, NULL, 0, NULL, ssid, security, channel);
    }
}

void bankai_wifi_sniff(const char *interface, const char *output_file) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    g_wifi_output = output_file;

    printf("[BANKAI] >>> A iniciar auditoria Wi-Fi na interface %s...\n", interface);

    handle = pcap_open_live(interface, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "[!] Erro ao abrir a interface %s: %s\n", interface, errbuf);
        return;
    }

    pcap_loop(handle, 0, packet_handler, NULL);
    pcap_close(handle);
}