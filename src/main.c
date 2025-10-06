#include "Logging.h"
#include "Data.h"

#include <stdio.h>

#define SSLB_DEBUG_LEVEL DEBUG

int main(){
	sslb_logging_init_outputs(2, stdout, fopen("./test", "a"));
	sslb_logging_init_format("[@d/@M/@y @h:@m:@s] \n\t @t");

	StringList* list = sslb_data_string_list_init();
	sslb_data_string_list_add(list, "pop1");
	sslb_data_string_list_add(list, "pop2");

	sslb_logging_log_line(sslb_data_string_list_pop(list));
	sslb_logging_log_line(sslb_data_string_list_pop(list));
	sslb_logging_close();
}
