#include <stdio.h>

#include "logger.h"
#include "printer.h"
#include "mylist.h"

// static const char *test_list[] = 
// {
//     "listitem1",
//     "listitem2",
//     "listitem3",
// };


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    LIST *myList = NULL;
    size_t currentListSize = 0U;
    int item1 = 7;
    int item2 = 24;
    int item3 = 19;
    void *dataBuffer = NULL;

    int *data[10] = {0};

    myList = create_list();
    if (myList == NULL) {
        LOG("Failed creating list..");
    }

    data[0] = add_to_list(myList, &item1, sizeof(int));
    if (data[0] == NULL) {
        LOG("Failed adding item to list");
    }

    data[1] = add_to_list(myList, &item2, sizeof(int));
    if (data[1] == NULL) {
        LOG("Failed adding item to list");
    }

    data[2] = add_to_list(myList, &item3, sizeof(int));
    if (data[2] == NULL) {
        LOG("Failed adding item to list");
    }

    currentListSize = get_list_count(myList);
    if (currentListSize != -1) {
        LOG("Current list size : %ld", currentListSize);
    }

    dataBuffer = get_item_at(myList, 0U);
    if (dataBuffer != NULL) {
        LOG("Item at index 0 is :%d", *((int*)dataBuffer));
    }

    dataBuffer = get_item_at(myList, 1U);
    if (dataBuffer != NULL) {
        LOG("Item at index 1 is :%d", *((int*)dataBuffer));
    }

    dataBuffer = get_item_at(myList, 2U);
    if (dataBuffer != NULL) {
        LOG("Item at index 2 is :%d", *((int*)dataBuffer));
    }

    dataBuffer = get_item_at(myList, 3U);
    if (dataBuffer != NULL) {
        LOG("Item at index 3 is :%d", *((int*)dataBuffer));
    }

    if (delete_from_list(myList, data[0]) == true) {
        dataBuffer = get_item_at(myList, 2U);
        if (dataBuffer != NULL) {
            LOG("Item at index 2 is :%d", *((int*)dataBuffer));
        }

        dataBuffer = get_item_at(myList, 0U);
        if (dataBuffer != NULL) {
            LOG("Item at index 0 is :%d", *((int*)dataBuffer));
        }
    }
    else {
        LOG("Delete failed!");
    }

    return 0;
}