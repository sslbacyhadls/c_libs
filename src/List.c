#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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

char* sslb_data_string_list_last(StringList* list){
    return list->currItem->string;
};

char* sslb_data_string_list_by_position(StringList* list, int position){
    if (position < list->size){
        StringListItem* item = list->currItem;

        for (int i = list->size; i > position+1; i--) {
            item = item->prevItem;
        }

        return item->string;
    } else {
        fprintf(stderr, "Error: Position %d doesn't exist in list\n", position);
    }
};


void sslb_data_string_list_view(StringList* list){
    char result[1000] = "[ ";

    for(int i = 0; i < list->size; i++){
        char string[100];
        if( i != list->size - 1){
            sprintf(string, "%d:\"%s\", ", i, sslb_data_string_list_by_position(list, i));
        } else {
            sprintf(string, "%d:\"%s\" ]\n", i, sslb_data_string_list_by_position(list, i));
        }
        strcat(result, string);
    }
    printf("%s", result);
};

void sslb_data_string_list_bulk_add(StringList* list, int n, ...){
    va_list ap;
	va_start(ap, n);

    for(int i = 0; i < n; i++){
        sslb_data_string_list_add(list, va_arg(ap, char*));
    }
};

void sslb_data_string_list_remove_by_position(StringList* list, int position){
    if (position < list->size-1 ){
        StringListItem* item = list->currItem;
        StringListItem* previousItem;
        
        for (int i = list->size; i > position + 2; i--) {
            item = item->prevItem;
            previousItem = item->prevItem;
        }

        item->prevItem = ((StringListItem*)item->prevItem)->prevItem;
        list->size--;

    } else if(position == list->size-1){
        sslb_data_string_list_pop(list);
    } else {
        fprintf(stderr, "Error: Position %d doesn't exist in list\n", position);
    }
};

void sslb_data_string_list_remove_by_data(StringList* list, char* data){
    for (int pos = 0; pos < list->size; pos++ ){
        if (sslb_data_string_list_by_position(list, pos) == data){
            sslb_data_string_list_remove_by_position(list, pos);
        }
    }
};


int sslb_data_string_list_find(StringList* list, char* data){
    for (int pos = 0; pos < list->size; pos++ ){
        if (sslb_data_string_list_by_position(list, pos) == data){
            return pos;
        }
    }
}