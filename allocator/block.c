#include <stdlib.h>

#include "block.h"

void block_split(struct block * block_to_split, size_t size)
{
    struct block * block2;
    size_t current_size = get_cur_block_size();
    if (current_size >= size + BLOCK_SIZE)
    {
        size_t split_size = current_size - (BLOCK_SIZE + size);
        set_cur_block_size(block_to_split, size);

        block2 = next_block(block_to_split);
        init_block(block2);
        set_cur_block_size(block2, split_size);
        set_prev_block_size(block2, size);

        if (get_block_is_last(block_to_split))
        {
            set_block_is_last(block_to_split);
            set_block_is_last(block2);
        }
        else
        {
            set_prev_block_size(next_block(block2), size_split);
        }
    }
    set_block_is_used(block_to_split, true);
}

//----------------
void block_merge(struct block * block1, struct block * block2)
{
    size_t block_size = get_cur_block_size(block1) + get_cur_block_size(block2);
    set_cur_block_size(block1);

}
