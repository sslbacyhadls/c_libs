#ifndef SSLB_DATA
#define SSLB_DATA

typedef struct {
    char* string;
    void* prevItem;
} StringListItem;

typedef struct {
    StringListItem* currItem;
    int size;
} StringList;

void sslb_data_string_list_add(StringList*, char*);

char* sslb_data_string_list_pop(StringList*);

StringList* sslb_data_string_list_init();

#endif