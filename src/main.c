#include "Logging.h"
#include <stdio.h>

#define SSLB_DEBUG_LEVEL DEBUG

int main(){
	sslb_logging_init_outputs(2, stdout, fopen("./test", "a"));
	sslb_logging_init_format("[@d/@M/@y @h:@m:@s] \n\t @t");

	sslb_logging_log_line("test1");
	sslb_logging_log_line("test3");
	sslb_logging_close();
}
