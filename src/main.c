#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "port_scanner.h"
#include "wifi_audit.h"

void print_help(const char *prog_name) {
    printf("========================================\n");
    printf("       BANKAI - Security Framework      \n");
    printf("========================================\n");
    printf("Uso:\n");
    printf("  sudo %s -m <modo> [opções]\n\n", prog_name);
    printf("Modos:\n");
    printf("  port                 - Executa o scanner de portas TCP\n");
    printf("  wifi                 - Executa a auditoria de Beacon Frames Wi-Fi\n\n");
    printf("Opções:\n");
    printf("  -t <ip>              - IP alvo para portas (ex: 127.0.0.1)\n");
    printf("  -i <interface>       - Interface Wi-Fi em modo monitor (ex: wlan0mon)\n");
    printf("  -o <ficheiro.json>   - Ficheiro JSON de saída (padrão: bankai_report.json)\n");
    printf("  -h                   - Ajuda\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char *mode = NULL;
    char *target = NULL;
    char *interface = NULL;
    char *output_file = "bankai_report.json";

    while ((opt = getopt(argc, argv, "m:t:i:o:h")) != -1) {
        switch (opt) {
            case 'm': mode = optarg; break;
            case 't': target = optarg; break;
            case 'i': interface = optarg; break;
            case 'o': output_file = optarg; break;
            case 'h':
            default: print_help(argv[0]); return 1;
        }
    }

    if (mode == NULL) {
        print_help(argv[0]);
        return 1;
    }

    // Inicializar o ficheiro JSON (Array)
    FILE *f = fopen(output_file, "w");
    if (f) {
        fprintf(f, "[\n");
        fclose(f);
    }

    if (strcmp(mode, "port") == 0) {
        if (!target) { fprintf(stderr, "[!] Erro: Falta o alvo (-t).\n"); return 1; }
        run_port_scanner(target, output_file);
    } else if (strcmp(mode, "wifi") == 0) {
        if (!interface) { fprintf(stderr, "[!] Erro: Falta a interface (-i).\n"); return 1; }
        bankai_wifi_sniff(interface, output_file);
    } else {
        fprintf(stderr, "[!] Modo desconhecido.\n");
        print_help(argv[0]);
        return 1;
    }

    // Fechar o Array JSON com segurança
    f = fopen(output_file, "a");
    if (f) {
        fprintf(f, "  {}\n]\n");
        fclose(f);
    }

    return 0;
}