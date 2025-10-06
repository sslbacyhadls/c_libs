#include "Data.h"
#include <stdlib.h>
#include <stdio.h>

void sslb_data_string_list_add(StringList* list, char* string){
    StringListItem* item = malloc(sizeof(StringListItem));
    item->string = string;
    item->prevItem = list->currItem;
    list->currItem = item;
};

char* sslb_data_string_list_pop(StringList* list){
    StringListItem* item = list->currItem;
    // free(list->currItem);
    list->currItem = item->prevItem;
    return item->string;
};

StringList* sslb_data_string_list_init(){
    StringList* list = malloc(sizeof(StringList));
    list->currItem = (StringListItem*)list;
};