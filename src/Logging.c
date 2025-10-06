#include "Logging.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 1000

Logging_config logging_config;

void sslb_logging_init_outputs(int n, ...){
	va_list ap;
	va_start(ap, n);
	
	if (n <= 0){
		fprintf(stderr, "Error: sslb_logging_init_outputs() expects at least one argument\n");
		return;
	}
	
	logging_config.outputs = malloc(sizeof(FILE*) * n);
	if (logging_config.outputs == NULL){
		fprintf(stderr, "Error: malloc failed in sslb_logging_init_outputs()\n");
		return;
	}
	
	for(int i = 0; i < n; i++){
		FILE* output = va_arg(ap, FILE*);
		if (output == NULL){
			fprintf(stderr, "Error: NULL pointer argument in sslb_logging_init_outputs()\n");
			free(logging_config.outputs);
			return;
		}
		
		if (ferror(output) != 0){
			fprintf(stderr, "Error: file descriptor invalid in sslb_logging_init_outputs()\n");
			free(logging_config.outputs);
			return;
		}
		
		if (fileno(output) < 0){
			fprintf(stderr, "Error: file descriptor invalid in sslb_logging_init_outputs()\n");
			free(logging_config.outputs);
			return;
		}
		
		logging_config.outputs[i] = output;
	}
	va_end(ap);
}

void sslb_logging_init_format(char* format){
	logging_config.format = format;
}


void add_in_buffer(char* buffer, int* offcet, int index, char* mbuff, int size){
	int size_gap = size - strlen(mbuff);
	char lbuff[size];

	for (int i = 0; i < size_gap; i++)
		lbuff[i] = '0';
	

	for (int j = 0; j < strlen(mbuff); j++)
		lbuff[ j + size_gap ] = mbuff[j];
	

	for (int k = 0; k < size; k++){
		buffer[index + *offcet] = lbuff[k];
		*offcet += 1;
	}
}


void sslb_logging_log_line(char * text){
	if (text == NULL)
		return;
	
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	if (tm == NULL){
		fprintf(stderr, "Error: localtime() failed\n");
		return;
	}
	
	int outputs_number = sizeof(logging_config.outputs) / sizeof(FILE*);
	if (outputs_number <= 0){
		fprintf(stderr, "Error: logging_config.outputs is empty\n");
		return;
	}
	
	char buffer[1000];

	for (int i = 0; i < 1000; i++)
		buffer[i] = '\0';

	unsigned int offcet = 0;

	if (logging_config.format == NULL){
		fprintf(stderr, "Error: logging_config.format is NULL\n");
		return;
	}

	for (int i = 0; i < strlen(logging_config.format); i++){
		if (logging_config.format[i - 1] == '@' ){
			switch(logging_config.format[i]){
				case 's':
					char sec[2];
					sprintf(sec, "%d", tm->tm_sec);
					add_in_buffer(buffer, &offcet, i, sec, 2);	
					offcet--;
					break;

				case 'm':
					char min[2];
					sprintf(min, "%d", tm->tm_min);
					add_in_buffer(buffer, &offcet, i, min, 2);	
					offcet--;
					break;

				case 'h':
					char hour[2];
					sprintf(hour, "%d", tm->tm_hour);
					add_in_buffer(buffer, &offcet, i, hour, 2);	
					offcet--;
					break;

				case 'd':
					char day[2];
					sprintf(day, "%d", tm->tm_mday);
					add_in_buffer(buffer, &offcet, i, day, 2);	
					offcet--;
					break;

				case 'M':
					char month[2];
					sprintf(month, "%d", tm->tm_mon);
					add_in_buffer(buffer, &offcet, i, month, 2);	
					offcet--;
					break;
				
				case 'y':
					char year[5];
					int year_size = snprintf(year, 5, "%d", tm->tm_year + 1900);
					add_in_buffer(buffer, &offcet, i, year, year_size);	
					offcet--;
					break;

				case 't':
					int textSize = strlen(text);
					if (text == NULL || textSize > 998){
						fprintf(stderr, "Error: text is NULL or too long\n");
						return;
					}
					add_in_buffer(buffer, &offcet, i, text, textSize);	
					offcet--;
					break;
			}
		} 

		else if ( logging_config.format[i] == '@' ){
			offcet--;
		} else {
			buffer[i + offcet] = logging_config.format[i];
		}
	}

	// fprintf(logging_config.outputs[1],"%s", buffer);
	for (int i = 0; i <= outputs_number; i++){
		fprintf(logging_config.outputs[i], "%s\n", buffer);	
	}
}

void sslb_logging_close(){
	int outputs_number = sizeof(logging_config.outputs) / sizeof(FILE*);
	for (int i = 0; i < outputs_number; i++){
		fclose(logging_config.outputs[i]);
	}
}
