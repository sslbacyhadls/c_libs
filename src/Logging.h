#ifndef SSLB_LOGGING
#define SSLB_LOGGING

#include <stdio.h>

typedef struct {
	FILE** outputs;
	char* format;
} Logging_config;

void sslb_logging_init_outputs(int, ...);

void sslb_logging_init_format(char*);

void sslb_logging_log_line(char *);

void sslb_logging_close();
#endif
