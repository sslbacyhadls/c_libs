#include "Logging.h"
#include "List.h"

#include <stdio.h>

#define SSLB_DEBUG_LEVEL DEBUG

int main(){
	sslb_logging_init_outputs(2, stdout, fopen("./test", "a"));
	sslb_logging_init_format("[@d/@M/@y @h:@m:@s] -- @t");

	StringList* list = sslb_data_string_list_init();
	sslb_data_string_list_bulk_add(list, 10, "pop0", "pop1", "pop2", "pop3", "pop4" ,"pop5", "pop6", "pop7", "pop8","pop9");
	sslb_data_string_list_view(list);
	sslb_data_string_list_remove_by_position(list, 2);
	sslb_data_string_list_remove_by_data(list, "pop8");
	printf("Pos: %d\n", sslb_data_string_list_find(list, "pop3"));
	sslb_data_string_list_view(list);

	sslb_logging_close();
}
