#include <stdio.h>

#include "logger.h"


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;


    LOG("Hello World!");
    LOG("Log test int:%d!", 10);

    return 0;
}