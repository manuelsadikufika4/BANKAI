#ifndef EXPORTER_H
#define EXPORTER_H

#include <stdio.h>

void bankai_export_json(const char *filename, const char *target, int port, const char *status, const char *ssid, const char *security, int channel);

#endif