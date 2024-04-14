#include <stdio.h>

#include "logger.h"
#include "printer.h"


static const char *test_list[] = 
{
    "Jessie",
    "Daniel",
    "Maribojoc",
};


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    print_list(test_list, sizeof(test_list) / sizeof(char*));

    return 0;
}