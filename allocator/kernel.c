#include <stdlib.h>

#include "kernel.h"

void * kernel_malloc(size_t size) {
    return malloc(size)
}
