#include <stdlib.h>
#include <assert.h>

#include "bigz.h"

bigz *
make_bigz(int size)
{
    bigz *new;

    assert(size > 0);
    new = (bigz *) malloc(sizeof(bigz));
    new->size = size;
    new->sign = POSITIVE;
    new->limbs = (unsigned int *) calloc(sizeof(unsigned int), size);

    return new;
}

void
free_bigz(bigz * n)
{
    free(n->limbs);
    n->limbs = NULL;
    free(n);
}
