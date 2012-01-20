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

    a = make_bigz(3);
    b = make_bigz(3);

    // a->limbs[0] = 6234245;
    // a->limbs[1] = 123405;
	a->limbs[0] = 1231241;
	a->limbs[1] = 1231241;
	a->limbs[2] = 121241;

	b->limbs[0] = 124101212;
	b->limbs[1] = 230124192;
	b->limbs[2] = 119241283;

    // b->limbs[0] = 501233;
    // b->limbs[1] = 23469899;

    c = bigz_umul(a, b);

    bigz_print(a);
    bigz_print(b);
    bigz_print(c);

    return 0;
}
