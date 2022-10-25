#include <stdlib.h>

struct block {
    size_t size_current;
    size_t size_previous;

    bool is_used;
    bool is_first;
    bool is_last;
};
