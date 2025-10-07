#include "Logging.h"
#include "ListString.h"
#include "List.h"

#include <stdio.h>

#define List sslb_list_string
#define Log sslb_logging
int main(){
	sslb_logging_init_outputs(2, stdout, fopen("./test", "a"));
	sslb_logging_init_format("[@d/@M/@y @h:@m:@s] -- @t");

	sslb_list_create(int);
	List_int* list = sslb_list_init_int();

	sslb_list_bulk_add_int(list, 2, 1, 2);

	printf("%d", sslb_list_pop_int(list));

	sslb_logging_close();
}
