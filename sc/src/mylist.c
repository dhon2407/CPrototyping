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
void *add_to_list(LIST *list, void *data, size_t size) {

    node_t *currentNode = NULL;
    node_t *newNode = NULL;

    if (list == NULL) {
        LOG("list is null!");
        return NULL;
    }

    if (data == NULL) {
        LOG("data is null!");
        return NULL;
    }

    if (size == 0U) {
        LOG("size is 0");
        return NULL;
    }

    newNode = malloc(sizeof(node_t));
    newNode->data = malloc(size);
    (void)memcpy(newNode->data, data, size);
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

    return newNode->data;
}

bool delete_from_list(LIST *list, void *data) {

    bool delStatus = false;
    node_t *currentNode = NULL;
    node_t *previousNode = NULL;

    if (list == NULL) {
        LOG("list is null!");
        return false;
    }

    if (data == NULL) {
        LOG("data is null!");
        return false;
    }

    currentNode = list->head;
    previousNode = list->head;

    if (currentNode->data == data) {
        free(currentNode->data);
        currentNode->data = NULL;
        list->head = currentNode->next;

        free(currentNode);
        currentNode = NULL;

        if (list->count > 0U) {
            list->count--;
        }
        return true;
    }

    currentNode = currentNode->next;
    while (currentNode != NULL)
    {
        if (currentNode->data == data)
        {
            free(currentNode->data);
            currentNode->data = NULL;
            previousNode->next = currentNode->next;
            
            free(currentNode);
            currentNode = NULL;
            
            if (list->count > 0U) {
                list->count--;
            }
            delStatus = true;
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    return delStatus;
}

size_t get_list_count(LIST *list) {
    
    if (list == NULL) {
        LOG("invalid parameter (list:%p)", list);
        return -1;
    }

    return list->count;
}

void *get_item_at(LIST *list, size_t index) {

    size_t currentIndex = 0U;
    node_t *resultNode = NULL;

    if (list == NULL) {
        LOG("list is null!");
        return NULL;
    }

    if (list->count == 0) {
        LOG("list is empty!");
        return NULL;
    }

    if (index >= list->count) {
        LOG("invalid index :%lu , list length:%lu", index, list->count);
        return NULL;
    }

    if (list->head == NULL) {
        LOG("List head is null");
        return NULL;
    }

    resultNode = list->head;
    while (currentIndex != index)
    {
        currentIndex++;
        resultNode = resultNode->next;
    }

    if (resultNode == NULL) {
        LOG("invalid data");
        return NULL;
    }

    return resultNode->data;
}

void free_list(LIST *list) {

    node_t *currentNode = NULL;
    node_t *nextNode = NULL;

    if (list == NULL) {
        LOG("list is null!");
        return;
    }

    currentNode = list->head;
    while (currentNode != NULL)
    {
        nextNode = currentNode->next;

        if (currentNode->data != NULL) {
            free(currentNode->data);
            currentNode->data = NULL;
        }
        free(currentNode);
        currentNode = nextNode;
    }

    free(list);

    return;
}