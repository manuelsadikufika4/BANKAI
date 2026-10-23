#include <stdio.h>
#include <stdlib.h>
#include "exporter.h"

void bankai_export_json(const char *filename, const char *target, int port, const char *status, const char *ssid, const char *security, int channel) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "[!] Erro ao abrir o ficheiro JSON para escrita: %s\n", filename);
        return;
    }

    fprintf(file, "  {\n");
    fprintf(file, "    \"tool\": \"BANKAI\",\n");
    if (target) {
        fprintf(file, "    \"type\": \"port_scan\",\n");
        fprintf(file, "    \"target\": \"%s\",\n", target);
        fprintf(file, "    \"port\": %d,\n", port);
        fprintf(file, "    \"status\": \"%s\"\n", status);
    } else {
        fprintf(file, "    \"type\": \"wifi_audit\",\n");
        fprintf(file, "    \"ssid\": \"%s\",\n", ssid ? ssid : "<Unknown>");
        fprintf(file, "    \"security\": \"%s\",\n", security ? security : "<Unknown>");
        fprintf(file, "    \"channel\": %d\n", channel);
    }
    fprintf(file, "  },\n");

    fclose(file);
}