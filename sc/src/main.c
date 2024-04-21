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
    int *printP = NULL;

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

    if (get_item_at(myList, 0U, (void**)&printP) == true) {
        LOG("Item at index 0 is :%d", *printP);
    }

    if (get_item_at(myList, 1U, (void**)&printP) == true) {
        LOG("Item at index 1 is :%d", *printP);
    }

    if (get_item_at(myList, 2U, (void**)&printP) == true) {
        LOG("Item at index 2 is :%d", *printP);
    }

    if (get_item_at(myList, 3U, (void**)&printP) == true) {
        LOG("Item at index 3 is :%d", *printP);
    }

    return 0;
}