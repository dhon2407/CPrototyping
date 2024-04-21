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

    myList = create_list();
    if (myList == NULL) {
        LOG("Failed creating list..");
    }

    if (add_to_list(myList, &item1, sizeof(int)) != true) {
        LOG("Failed adding item to list");
    }

    if (add_to_list(myList, &item2, sizeof(int)) != true) {
        LOG("Failed adding item to list");
    }

    if (add_to_list(myList, &item3, sizeof(int)) != true) {
        LOG("Failed adding item to list");
    }

    if (get_list_count(myList, &currentListSize) != -1) {
        LOG("Current list size : %ld", currentListSize);
    }

    if (get_item_at(myList, 0U, &dataBuffer) == true) {
        LOG("Item at index 0 is :%d", *((int*)dataBuffer));
    }

    if (get_item_at(myList, 1U, &dataBuffer) == true) {
        LOG("Item at index 1 is :%d", *((int*)dataBuffer));
    }

    if (get_item_at(myList, 2U, &dataBuffer) == true) {
        LOG("Item at index 2 is :%d", *((int*)dataBuffer));
    }

    if (get_item_at(myList, 3U, &dataBuffer) == true) {
        LOG("Item at index 3 is :%d", *((int*)dataBuffer));
    }

    return 0;
}