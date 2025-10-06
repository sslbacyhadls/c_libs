#include "List.h"
#include <stdlib.h>
#include <stdio.h>

void sslb_data_string_list_add(StringList* list, char* string){
    StringListItem* item = malloc(sizeof(StringListItem));
    item->string = string;
    item->prevItem = list->currItem;
    list->currItem = item;
    list->size++;
};

char* sslb_data_string_list_pop(StringList* list){
    if(list->size > 0){
        StringListItem* item = list->currItem;
        list->currItem = item->prevItem;
        list->size--;
        return item->string;
    } else {
        return "";
    }
};

StringList* sslb_data_string_list_init(){
    StringList* list = malloc(sizeof(StringList));
    list->size = 0;
    list->currItem = (StringListItem*)list;
};