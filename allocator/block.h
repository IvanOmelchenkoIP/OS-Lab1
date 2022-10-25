#include <stdlib.h>

#include "accocator_impl.h"

struct block {
    size_t size_cur;
    size_t size_prev;

    bool is_used;
    bool is_first;
    bool is_last;
};

void block_split(struct block *, size_t);

void block_merge(struct block *, struct block *);


inline void * block_to_payload(struct block * mem_block)
{
    return (char *)block + ALLIGN(sizeof(struct block))
}

inline void * payload_to_block(void * payload_ptr)
{
    return (block *)(payload_ptr - ALLIGN(sizeof(struct block)))
}

// cur block size get, set

inline size_t get_cur_block_size(struct block * mem_block)
{
    return mem_block->size_cur;
}

inline void set_cur_block_size(struct block * mem_block, size_t new_size)
{
    mem_block->size_cur = new_size;
}

// prev block size get, set

inline size_t get_prev_block_size(struct block * mem_block)
{
    return mem_block->size_prev;
}

inline void set_prev_block_size(struct block * mem_block, size_t new_size)
{
    mem_block->size_prev = new_size;
}

// flag used get, set

inline bool get_block_is_used(struct block * mem_block)
{
    return mem_block->is_used;
}

inline void set_block_is_used(struct block * mem_block, bool state)
{
    mem_block->is_used = state;
}

//flag is first get, set

inline bool get_block_is_first(struct block * mem_block)
{
    return mem_block->size_prev;
}

inline void set_block_is_first(struct block * mem_block, bool state)
{
    mem_block->is_first = state;
}

// flag is last get, set

inline bool get_block_is_last(struct block * mem_block)
{
    return mem_block->is_last;
}

inline void set_block_is_last(struct block * mem_block, bool state)
{
    mem_block->is_last = state;
}

