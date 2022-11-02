#include <stdlib.h>

#include "config.h"
#include "kernel.h"
#include "block.h"
#include "allocator.h"

#define ARENA_SIZE (DEFAULT_PAGE_SIZE * DEFAULT_ARENA_PAGES_SIZE)

static struct block * arena = NULL;

sattic int arena_alloc()
{
    arena = kernel_malloc(ARENA_SIZE);
    if (arena == NULL) return -1;
    arena_init(arena, ARENA_SIZE - BLOCK_STRUCT_SIZE);
    return 0;
}

void * mem_alloc(size_t alloc_size)
{
    struct block * alloc_block;




}

void mem_free(void * ptr)
{
    struct block * block = payload_to_block((char *)ptr);
    set_block_is_used(block, false);
}
