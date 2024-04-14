#include "logger.h"
#include "printer.h"

void print_list(const char **nameList, size_t itemCount)
{
    size_t i = 0;

    for (i = 0; i < itemCount; i++)
    {
        LOG("Item %lu : %s", i + 1, nameList[i]);
    }
}