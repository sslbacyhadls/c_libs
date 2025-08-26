#include "Logging.h"
#include <stdio.h>

int main(){
	sslb_logging_init_outputs(1, stdout);
	sslb_logging_init_format("@h:@m:@s y/@M/@d @t");
	sslb_logging_log_line("test");
	sslb_logging_log_line("test123");
	sslb_logging_log_line("test323");
	sslb_logging_log_line("test123123123");
}
