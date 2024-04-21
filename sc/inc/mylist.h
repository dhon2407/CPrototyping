#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdbool.h>

typedef struct mlist LIST;

LIST *create_list(void);
bool add_to_list(LIST *list, void *data, size_t size);
bool delete_from_list(LIST *list, void *data, size_t size);
bool get_item_at(LIST *list, size_t index, void **data);
int get_list_count(LIST *list, size_t *size);
void free_list(LIST *list);


#endif