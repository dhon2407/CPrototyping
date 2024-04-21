#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "mylist.h"

typedef struct node {
    void *data;
    struct node *next;
} node_t;

typedef struct mlist {
    node_t *head;
    size_t count; 
} LIST;

LIST *create_list(void) {
    LIST *newList = malloc(sizeof(LIST));

    newList->count = 0;
    newList->head = NULL;

    return newList;
}
bool add_to_list(LIST *list, void *data, size_t size) {

    node_t *currentNode = NULL;
    node_t *newNode = NULL;

    if (list == NULL) {
        LOG("list is null!");
        return false;
    }

    if (data == NULL) {
        LOG("data is null!");
        return false;
    }

    if (size == 0U) {
        LOG("size is 0");
        return false;
    }

    newNode = malloc(sizeof(node_t));
    newNode->data = malloc(size);
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {
        currentNode = list->head;
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }

        currentNode->next = newNode;
    }

    list->count++;

    return true;
}

bool delete_from_list(LIST *list, void *data, size_t size) {
    (void)list;
    (void)data;
    (void)size;
    return false;
}

int get_list_count(LIST *list, size_t *size) {
    
    if (list == NULL) {
        LOG("invalid parameter (list:%p, size:%p)", list, size);
        return -1;
    }

    *size = list->count;

    return 0;
}

bool get_item_at(LIST *list, size_t index, void **data) {

    size_t currentIndex = 0U;
    node_t *resultNode = NULL;

    if (list == NULL) {
        LOG("list is null!");
        return false;
    }

    if (list->count == 0) {
        LOG("list is empty!");
        return false;
    }

    if (index >= list->count) {
        LOG("invalid index");
        return false;
    }

    if (list->head == NULL) {
        LOG("List head is null");
        return false;
    }

    resultNode = list->head;
    while (currentIndex != index)
    {
        currentIndex++;
        resultNode = resultNode->next;
    }

    if (resultNode == NULL) {
        LOG("invalid data");
        return false;
    }

    *data = resultNode->data;

    return true;
}