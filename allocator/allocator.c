#include <stdlib.h>

#include "block.h"
#include "allocator.h"

void * mem_alloc(size_t alloc_size)
{
    struct block * alloc_block;


}

void mem_free(void * ptr)
{
    struct block * block = payload_to_block((char *)ptr);
    set_block_is_used(block, false);
}
