#include <stdio.h>

#include "bigz.h"

void
bigz_print(bigz * n)
{
    int i;

    if (n->sign == 0)
        printf("-");
    else
        printf("+");
    for (i = 0; i < n->size; i++)
        printf("%10u ", n->limbs[i]);
    printf("\n");
}

int
main()
{
    int i;
    bigz *a, *b, *c;

    a = make_bigz(4);
    b = make_bigz(3);

    a->limbs[0] = 6;

    b->limbs[0] = 57;

    c = bigz_usub(a, b);

    bigz_print(a);
    bigz_print(b);
    bigz_print(c);

    return 0;
}
