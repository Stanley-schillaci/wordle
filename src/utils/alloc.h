#ifndef ALLOC_H_
#define ALLOC_H_

#include <stddef.h>

void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void *xcalloc(size_t size);

#endif
