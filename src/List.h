#ifndef SSLB_LIST
#define SSLB_LIST

typedef struct {
    char* string;
    void* prevItem;
} StringListItem;

typedef struct {
    StringListItem* currItem;
    int size;
} StringList;

// typedef struct {
//     int string;
//     void* prevItem;
// } IntListItem;

// typedef struct {
//     IntListItem* currItem;
//     int size;
// } IntList;


void sslb_data_string_list_add(StringList*, char*);

void sslb_data_string_list_bulk_add(StringList*, int, ...);

char* sslb_data_string_list_pop(StringList*);

StringList* sslb_data_string_list_init();

char* sslb_data_string_list_last(StringList*);

char* sslb_data_string_list_by_position(StringList*, int);

void sslb_data_string_list_view(StringList*);

void sslb_data_string_list_remove_by_position(StringList*, int);

void sslb_data_string_list_remove_by_data(StringList*, char*);

int sslb_data_string_list_find(StringList*, char*);

#endif