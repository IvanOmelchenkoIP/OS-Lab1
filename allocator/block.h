#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "allocator_impl.h"

struct block {
    size_t size_cur;
    size_t size_prev;

    bool is_used;
    bool is_first;
    bool is_last;
};

#define BLOCK_SIZE ALLIGN(sizeof(struct block)

// payload

static inline void* block_to_payload(struct block* mem_block)
{
    return ((char*)mem_block + BLOCK_SIZE));
}

static inline void* payload_to_block(void* payload_ptr)
{
    return (struct block*)(payload_ptr - BLOCK_SIZE));
}

// cur block size get, set

static inline size_t get_cur_block_size(struct block* mem_block)
{
    return mem_block->size_cur;
}

static inline void set_cur_block_size(struct block* mem_block, size_t new_size)
{
    mem_block->size_cur = new_size;
}

// prev block size get, set

static inline size_t get_prev_block_size(struct block* mem_block)
{
    return mem_block->size_prev;
}

static inline void set_prev_block_size(struct block* mem_block, size_t new_size)
{
    mem_block->size_prev = new_size;
}

// flag used get, set

static inline bool get_block_is_used(struct block* mem_block)
{
    return mem_block->is_used;
}

static inline void set_block_is_used(struct block* mem_block, bool state)
{
    mem_block->is_used = state;
}

//flag is first get, set

static inline bool get_block_is_first(struct block* mem_block)
{
    return mem_block->size_prev;
}

static inline void set_block_is_first(struct block* mem_block, bool state)
{
    mem_block->is_first = state;
}

// flag is last get, set

static inline bool get_block_is_last(struct block* mem_block)
{
    return mem_block->is_last;
}

static inline void set_block_is_last(struct block* mem_block, bool state)
{
    mem_block->is_last = state;
}

// next and prev blocks

static inline struct block* next_block (const struct block* mem_block)
{
    return (struct block*)((char*)mem_block + BLOCK_SIZE + get_cur_block_size(mem_block));
}

static inline struct block* prev_block (const struct block* mem_block)
{
    return (struct block*)((char*)mem_block - BLOCK_SIZE - get_cur_block_size(mem_block));
}

// init
static inline void init_block(struct block* block)
{
    block->is_used = false;
    block->is_first = false;
    block->is_last = false;
}

static inline void init_arena(struct block* block, size_t init_size)
{
    init_block(block);
    set_cur_block_size(block, init_size);
    set_prev_block_size(block, 0);
    set_block_is_first(block, true);
    set_block_is_last(block, true);
}

void block_split(struct block*, size_t);

void block_merge(struct block*, struct block*);
