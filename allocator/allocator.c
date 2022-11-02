#include <stdlib.h>

#include "config.h"
#include "kernel.h"
#include "block.h"
#include "allocator.h"

#define ARENA_SIZE (DEFAULT_PAGE_SIZE * DEFAULT_ARENA_PAGES_SIZE)

static struct block * first_arena = nullptr;

static int arena_alloc()
{
    first_arena = kernel_malloc(ARENA_SIZE);
    if (first_arena == nullptr) return 0;
    arena_init(first_arena, ARENA_SIZE - BLOCK_STRUCT_SIZE);
    return 1;
}


void * first_fit(size_t alloc_size)
{
    struct block * cur_block = first_arena;
    do
    {
        if (get_cur_block_size(block) <= alloc_size && !get_block_is_used(block)) return cur_block;
        cur_block = next_block(cur_block);
    } while (!get_block_is_last(cur_block));
    return nullptr;
}


void * mem_alloc(size_t alloc_size)
{
    struct block * alloc_block;

    if (first_arena == nullptr)
    {
        if (arena_alloc() == 0) return nullptr;
    }

    alloc_block = first_fit(alloc_size);
    return alloc_block;
}

void mem_free(void * ptr)
{
    struct block * freed_block = payload_to_block((char *)ptr);
    set_block_is_used(freed_block, false);
    block_merge(freed_block, next_block(freed_block));
}

void mem_show()
{
    if (first_arena == nullptr)
    {
        println("The first arena was not created!");
        return;
    }

    struct block * cur_block = first_arena;
    do
    {
        bool is_used = get_block_is_used(cur_block);
        bool is_first = get_block_is_first(cur_block);
        bool is_last = get_block_is_last(cur_block);
        size_t cur_size = get_cur_block_size(cur_block);
        size_t prev_size = get_prev_block_size(cur_block);
        printf("block is used: %s, block is first: %s, block is last: %s, current block size: %zu, previous block size: %zu\n",
               is_used ? "true": "false", is_first ? "true" : "false", is_last ? "true" : "false", cur_size, prev_size);

        block = next_block(block);
    } while (!get_block_is_last(cur_block));
}

void mem_realloc()
{

}
