#ifndef MY_LIST_H
#define MY_LIST_H

#include <stdbool.h>

typedef struct mlist LIST;

LIST *create_list(void);
void *add_to_list(LIST *list, void *data, size_t size);
void *get_item_at(LIST *list, size_t index);
bool delete_from_list(LIST *list, void *data);
size_t get_list_count(LIST *list);
void free_list(LIST *list);


#endif