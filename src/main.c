#include "Logging.h"
#include "List.h"

#include <stdio.h>

#define SSLB_DEBUG_LEVEL DEBUG

int main(){
	sslb_logging_init_outputs(2, stdout, fopen("./test", "a"));
	sslb_logging_init_format("[@d/@M/@y @h:@m:@s] -- @t");

	StringList* list = sslb_data_string_list_init();
	sslb_data_string_list_bulk_add(list, 10, "pop1", "pop2", "pop3", "pop4","pop5", "pop6", "pop7", "pop8","pop9", "pop10");
	sslb_data_string_list_view(list);
	sslb_logging_log_line(sslb_data_string_list_pop(list));

	sslb_data_string_list_bulk_add(list, 3, "2121", "32312", "123");
	sslb_logging_log_line(sslb_data_string_list_last(list));
	sslb_logging_log_line(sslb_data_string_list_by_position(list, 0));
	sslb_data_string_list_view(list);

	sslb_logging_close();
}
