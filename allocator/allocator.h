#include <stdlib.h>

void * mem_alloc(size_t);
void mem_show(const char *);
void * mem_realloc(struct block *, size_t);
void * mem_free(struct block *);
