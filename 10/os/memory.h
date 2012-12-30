#ifndef _KOZOS_MEMORY_H_INCLUDE_
#define _KOZOS_MEMORY_H_INCLUDE_

int kzmem_init(void);
void *kzmem_alloc(int size);
void kzmem_free(void *mem);

#endif
