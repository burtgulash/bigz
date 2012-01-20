#include <stdio.h>
#include <stdlib.h>

#include "bigz.h"

void
bigz_print(bigz * n)
{
    int i;

    if (n->sign == NEGATIVE)
        printf("-");
    else
        printf("+");
    for (i = 0; i < n->size; i++)
        printf("%11u ", n->limbs[i]);
    printf("\n");
}

int
main()
{
    int i;
    bigz *a, *b, *c;

    a = make_bigz(1);
    b = make_bigz(1);

    for (i = 0; i < a->size; i++)
        a->limbs[i] = rand() * rand();
    for (i = 0; i < b->size; i++)
        b->limbs[i] = rand() * rand();

    c = bigz_mul(a, b);

    bigz_print(a);
    bigz_print(b);
    bigz_print(c);

    return 0;
}
