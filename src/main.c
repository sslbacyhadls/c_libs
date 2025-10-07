#include "Logging.h"
#include "List.h"

#include <stdio.h>

#define List sslb_list_string
#define Log sslb_logging
int main(){
	sslb_logging_init_outputs(2, stdout, fopen("./test", "a"));
	sslb_logging_init_format("[@d/@M/@y @h:@m:@s] -- @t");


	
	StringList* list = sslb_list_string_init();
	StringList* list2 = sslb_list_string_init();

	sslb_list_string_bulk_add(list, 10, "pop0", "pop1", "pop2", "pop3", "pop4" ,"pop5", "pop6", "pop7", "pop8","pop9");
	sslb_list_string_bulk_add(list2, 10, "pop0", "pop1", "pop2", "pop3", "pop4" ,"pop5", "pop6", "pop7", "pop8","pop9");
	if(sslb_list_string_is_equals(list, list2)){
		sslb_logging_log_line("equals!");
	} else {
		sslb_logging_log_line("not equals! :(");
	}

	sslb_logging_close();
}
