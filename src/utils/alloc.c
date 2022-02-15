#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void *xmalloc(size_t size)
{
    void *res = malloc(size);
    if (res == NULL && size != 0)
        abort();
    return res;
}

void *xrealloc(void *ptr, size_t size)
{
    void *res = realloc(ptr, size);
    if (res == NULL && size != 0)
        abort();
    return res;
}

void *xcalloc(size_t size)
{
    void *res = xmalloc(size);
    memset(res, 0, size);
    return res;
}
