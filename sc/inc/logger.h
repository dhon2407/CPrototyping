#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

#define LOG(format, ...) \
    printf("[FUNC:%s][LINE:%d] "format"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)


#endif //LOGGER_H