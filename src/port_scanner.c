#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "port_scanner.h"
#include "exporter.h"

#define START_PORT 1
#define END_PORT 1024
#define NUM_THREADS 50

typedef struct {
    const char *target;
    const char *output_file;
} scan_args_t;

pthread_mutex_t scan_lock;
int global_current_port = START_PORT;
const char *g_target = NULL;
const char *g_output = NULL;

void *scan_ports_worker(void *arg) {
    (void)arg;
    int port;
    struct sockaddr_in target_addr;
    
    while (1) {
        pthread_mutex_lock(&scan_lock);
        if (global_current_port > END_PORT) {
            pthread_mutex_unlock(&scan_lock);
            break;
        }
        port = global_current_port++;
        pthread_mutex_unlock(&scan_lock);

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;

        memset(&target_addr, 0, sizeof(target_addr));
        target_addr.sin_family = AF_INET;
        target_addr.sin_port = htons(port);
        inet_pton(AF_INET, g_target, &target_addr.sin_addr);

        if (connect(sock, (struct sockaddr *)&target_addr, sizeof(target_addr)) == 0) {
            pthread_mutex_lock(&scan_lock);
            printf("[+] Porta %d: Aberta\n", port);
            bankai_export_json(g_output, g_target, port, "open", NULL, NULL, 0);
            pthread_mutex_unlock(&scan_lock);
        }
        close(sock);
    }
    return NULL;
}

void run_port_scanner(const char *target, const char *output_file) {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&scan_lock, NULL);
    g_target = target;
    g_output = output_file;

    printf("[*] A iniciar Port Scanner na BANKAI para %s (Portas %d-%d)...\n", target, START_PORT, END_PORT);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, scan_ports_worker, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&scan_lock);
    printf("[*] Varrimento de portas concluído.\n");
}