#include <stdlib.h>

struct block {
    size_t size_current;
    size_t size_previous;

    bool is_used;
    bool is_first;
    bool is_last;
};

void block_split(struct block *, size_t);

void block_merge(struct block *, struct block *);
