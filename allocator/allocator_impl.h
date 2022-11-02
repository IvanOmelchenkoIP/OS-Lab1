#include <stdalign.h>
#include <stdio.h>
#include <stddef.h>

#define ALIGNMENT _Alignof(max_align_t)
#define ALIGN(size) ((size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
