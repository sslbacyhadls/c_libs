#include "Logging.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

Logging_config logging_config;

void sslb_logging_init_outputs(int n, ...){
	va_list ap;
	va_start(ap, n);
	
	logging_config.outputs = malloc(sizeof(FILE*) * n);
	for(int i; i<n; i++){
		logging_config.outputs[i] = va_arg(ap, FILE*);
	}
	va_end(ap);
}

void sslb_logging_init_format(char* format){
	logging_config.format = format;
}


void add_in_buffer(char* buffer, int* offcet, int index, char* mbuff, int size){
	int size_gap = size - strlen(mbuff);
	char lbuff[size];

	for (int i = 0; i < size_gap; i++){
		lbuff[i] = '0';	
	}

	for (int j = 0; j < strlen(mbuff); j++){
		lbuff[ j + size_gap ] = mbuff[j];
	}

	for (int k = 0; k < size; k++){
		buffer[ index + *offcet ] = lbuff[k];
		*offcet += 1;
	}
}

void sslb_logging_log_line(char * text){
	time_t t = time(NULL);
	struct tm* tm = localtime(&t);
	
	int outputs_number = sizeof(logging_config.outputs) / sizeof(FILE*);
	char buffer[1000];
	unsigned int offcet = 0;


	for (int i = 0; i < strlen(logging_config.format); i++){
		if( logging_config.format[i - 1] == '@' ){
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
					char year[4];
					sprintf(year, "%d", tm->tm_year + 1900);
					add_in_buffer(buffer, &offcet, i, year, 4);	
					offcet += 2;
					break;

				case 't':
					int textSize = strlen(text);
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

	printf("%s\n", buffer);
	//for (int i; i < outputs_number; i++){
	//	fprintf(logging_config.outputs[i], "%s", buffer);	
	//}
}

