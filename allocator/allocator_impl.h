#define ALIGNMENT _Alignof(max_align_t)
#define AlIGN(size) ((size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
