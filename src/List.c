#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

void sslb_list_string_add(StringList* list, char* string){
    StringListItem* item = malloc(sizeof(StringListItem));
    item->string = string;
    item->prevItem = list->currItem;
    list->currItem = item;
    list->size++;
};

char* sslb_list_string_pop(StringList* list){
    if(list->size > 0){
        StringListItem* item = list->currItem;
        list->currItem = item->prevItem;
        list->size--;
        return item->string;
    } else {
        return "";
    }
};

StringList* sslb_list_string_init(){
    StringList* list = malloc(sizeof(StringList));
    list->size = 0;
    list->currItem = (StringListItem*)list;
};

char* sslb_list_string_last(StringList* list){
    return list->currItem->string;
};

char* sslb_list_string_by_position(StringList* list, int position){
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


void sslb_list_string_view(StringList* list){
    char result[1000] = "[ ";

    for(int i = 0; i < list->size; i++){
        char string[100];
        if( i != list->size - 1){
            sprintf(string, "%d:\"%s\", ", i, sslb_list_string_by_position(list, i));
        } else {
            sprintf(string, "%d:\"%s\" ]\n", i, sslb_list_string_by_position(list, i));
        }
        strcat(result, string);
    }
    printf("%s", result);
};

void sslb_list_string_bulk_add(StringList* list, int n, ...){
    va_list ap;
	va_start(ap, n);

    for(int i = 0; i < n; i++){
        sslb_list_string_add(list, va_arg(ap, char*));
    }
};

void sslb_list_string_remove_by_position(StringList* list, int position){
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
        sslb_list_string_pop(list);
    } else {
        fprintf(stderr, "Error: Position %d doesn't exist in list\n", position);
    }
};

void sslb_list_string_remove_by_data(StringList* list, char* data){
    sslb_list_string_remove_by_position(list, sslb_list_string_find(list, data));
};


int sslb_list_string_find(StringList* list, char* data){
    for (int pos = 0; pos < list->size; pos++ ){
        if (sslb_list_string_by_position(list, pos) == data){
            return pos;
        }
    }
}

bool sslb_list_string_is_equals(StringList* list1, StringList* list2){
    if( list1->size != list2->size){
        return false;
    }

    for(int i = 0; i < list1->size; i++){
        if(sslb_list_string_by_position(list1, i) != sslb_list_string_by_position(list2, i)){
            return false;
        }
    }

    return true;
};