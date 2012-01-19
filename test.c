#include <stdio.h>

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

    a->limbs[0] = 6234245;

    b->limbs[0] = 501233;

    c = bigz_umul(a, b);

    bigz_print(a);
    bigz_print(b);
    bigz_print(c);

    return 0;
}
