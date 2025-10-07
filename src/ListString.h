#ifndef SSLB_LIST
#define SSLB_LIST

#include <stdbool.h>

typedef struct {
    char* string;
    void* prevItem;
} StringListItem;

typedef struct {
    StringListItem* currItem;
    int size;
} StringList;

void sslb_list_string_add(StringList*, char*);

void sslb_list_string_bulk_add(StringList*, int, ...);

char* sslb_list_string_pop(StringList*);

StringList* sslb_list_string_init();

char* sslb_list_string_last(StringList*);

char* sslb_list_string_by_position(StringList*, int);

void sslb_list_string_view(StringList*);

void sslb_list_string_remove_by_position(StringList*, int);

void sslb_list_string_remove_by_data(StringList*, char*);

int sslb_list_string_find(StringList*, char*);

bool sslb_list_string_is_equals(StringList*, StringList*);

#endif