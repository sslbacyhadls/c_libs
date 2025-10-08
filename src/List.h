#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

bool sslb_list_equals(void* first, void* second){
    if(*(char*)first == *(char*)second){
        return true;
    }
    return false;
}

#define sslb_list_create(type)                                              \
    typedef struct { type data; void* prevItem; } ListItem_##type;          \
    typedef struct { ListItem_##type* currItem; int size; } List_##type;    \ 
                                                                            \
    List_##type* sslb_list_init_##type(){                                   \
        List_##type* list = (List_##type*)malloc(sizeof(List_##type));                    \
        list->size = 0;                                                     \
        list->currItem = (ListItem_##type*)list;                            \
    };                                                                      \
                                                                            \
    void sslb_list_add_##type(List_##type* list, type data){                \
    ListItem_##type* item = malloc(sizeof(ListItem_##type));                \
        item->data = data;                                                  \
        item->prevItem = list->currItem;                                    \
        list->currItem = item;                                              \
        list->size++;                                                       \
    };                                                                      \
                                                                            \
    type sslb_list_pop_##type(List_##type* list){                           \
        if(list->size > 0){                                                 \
            ListItem_##type* item = list->currItem;                         \
            list->currItem = item->prevItem;                                \
            list->size--;                                                   \
            return item->data;                                              \
        } else {                                                            \
            return (type)0;                                                 \
        }                                                                   \
    };                                                                      \
                                                                            \
    type sslb_list_last_##type(List_##type* list){                          \
        return list->currItem->data;                                        \
    };                                                                      \
                                                                            \
    type sslb_list_by_position_##type(List_##type* list, int position){     \
        if (position < list->size){                                         \
            ListItem_##type* item = list->currItem;                         \
                                                                            \
            for (int i = list->size; i > position+1; i--) {                 \
                item = item->prevItem;                                      \
            }                                                               \
                                                                            \
            return item->data;                                              \
        } else {                                                            \
            fprintf(stderr, "Error: Position %d doesn't exist in list\n", position);\
        }                                                                   \
    };                                                                      \
                                                                            \
                                                                            \
                                                                            \
    void sslb_list_bulk_add_##type(List_##type* list, int n, ...){          \
        va_list ap;                                                         \
        va_start(ap, n);                                                    \
                                                                            \
        for(int i = 0; i < n; i++){                                         \
            sslb_list_add_##type(list, va_arg(ap, type));                   \
        }                                                                   \
    };                                                                      \
                                                                            \
    void sslb_list_remove_by_position_##type(List_##type* list, int position){\
        if (position < list->size-1 ){                                      \
            ListItem_##type* item = list->currItem;                         \
            ListItem_##type* previousItem;                                  \
                                                                            \
            for (int i = list->size; i > position + 2; i--) {               \
                item = item->prevItem;                                      \
                previousItem = item->prevItem;                              \  
            }                                                               \
                                                                            \
            item->prevItem = ((ListItem_##type*)item->prevItem)->prevItem;  \
            list->size--;                                                   \
                                                                            \
        } else if(position == list->size-1){                                \
            sslb_list_pop_##type(list);                                     \
        } else {                                                            \
            fprintf(stderr, "Error: Position %d doesn't exist in list\n", position);\
        }                                                                   \
    };                                                                      \
                                                                            \
                                                                            \
                                                                            \
    int sslb_list_find_##type(List_##type* list, type data){                \
        for (int pos = 0; pos < list->size; pos++ ){                        \
            type pos_data = sslb_list_by_position_##type(list, pos);        \
            if (sslb_list_equals(&pos_data, &data)){                        \
                return pos;                                                 \
            }                                                               \
        }                                                                   \
    }                                                                       \
                                                                            \
    void sslb_list_remove_by_data_##type(List_##type* list, type data){     \
        sslb_list_remove_by_position_##type(list, sslb_list_find_##type(list, data));\
    };                                                                      \
    bool sslb_list_is_equals_##type(List_##type* list1, List_##type* list2){\
        if( list1->size != list2->size){                                    \
            return false;                                                   \
        }                                                                   \
                                                                            \
        for(int i = 0; i < list1->size; i++){                               \
            type first = sslb_list_by_position_##type(list1, i);            \
            type second = sslb_list_by_position_##type(list2, i);           \
            if(!sslb_list_equals(&first, &second)){                         \
                return false;                                               \
            }                                                               \
        }                                                                   \
                                                                            \
        return true;                                                        \
    };