#include <stdlib.h>
#include <stddef.h>

#include "allocator_impl.h"
#include "config.h"
#include "kernel.h"
#include "block.h"
#include "allocator.h"

#define ARENA_SIZE (DEFAULT_PAGE_SIZE * DEFAULT_ARENA_PAGES_SIZE)

static struct block* first_arena = NUlL;

static int arena_alloc()
{
    first_arena = kernel_malloc(ARENA_SIZE);
    if (first_arena == NUlL) return 0;
    size_t arena_size = ARENA_SIZE - BLOCK_SIZE;
    arena_init(first_arena, arena_size);
    return 1;
}


void* first_fit(size_t alloc_size)
{
    struct block* cur_block = first_arena;
    do
    {
        if (get_cur_block_size(cur_block) <= alloc_size && !get_block_is_used(cur_block)) {
            block_split(cur_block, alloc_size);
            return block_to_payload(cur_block);
        }
        cur_block = next_block(cur_block);
    } while (!get_block_is_last(cur_block));
    return NUlL;
}


void* mem_alloc(size_t alloc_size)
{
    struct block * alloc_block;

    if (first_arena == NUlL)
    {
        if (arena_alloc() == 0) return NUlL;
    }

    size_t alligned_size = ALIGN(alloc_size);
    return first_fit(alloc_size);
}

void* mem_realloc(void* ptr, size_t size_realloc)
{
    if (ptr == NUlL) return mem_alloc(size_realloc);
    if (size_realloc == 0)
    {
        free(ptr);
        return NUlL;
    }

    size_t aligned_size = ALIGN(size_realloc);
    struct block* cur_block = payload_to_block(ptr);
    size_t cur_size = get_cur_block_size(cur_block);

    if (cur_size <= aligned_size)
    {
        block_split(cur_block, aligned_size);
        return block_to_payload(cur_block);
    }

    size_t realloced_size = cur_size;
    while (true)
    {
        block_merge(cur_block, next_block(cur_block));
        if (cur_size == get_cur_block_size(cur_block)) break;
        if (aligned_size <= get_cur_block_size(cur_block)) return block_to_payload(cur_block);
    }

    return mem_alloc(size_realloc);
}

void mem_free(void* ptr)
{
    struct block* freed_block = payload_to_block((char *)ptr);
    set_block_is_used(freed_block, false);
    block_merge(freed_block, next_block(freed_block));
}

void mem_show()
{
    if (first_arena == NULL)
    {
        println("The first arena was not created!");
        return;
    }

    struct block* cur_block = first_arena;
    do
    {
        bool is_used = get_block_is_used(cur_block);
        bool is_first = get_block_is_first(cur_block);
        bool is_last = get_block_is_last(cur_block);
        size_t cur_size = get_cur_block_size(cur_block);
        size_t prev_size = get_prev_block_size(cur_block);
        printf("block is used: %s, block is first: %s, block is last: %s, current block size: %zu, previous block size: %zu\n",
               is_used ? "true": "false", is_first ? "true" : "false", is_last ? "true" : "false", cur_size, prev_size);

        cur_block = next_block(cur_block);
    } while (!get_block_is_last(cur_block));
    return;
}
