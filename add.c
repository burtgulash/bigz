#include <stdlib.h>

#include "bigz.h"

bigz 
*bigz_uadd(bigz * a, bigz * b)
{
    int carry, i, longer_s, shorter_s;
    unsigned int *longer;
    bigz *sum;

    longer_s = a->size;
    shorter_s = b->size;
    if (longer_s < shorter_s) {
        longer = b->limbs;
        longer_s = b->size;
        shorter_s = a->size;
    } else
        longer = a->limbs;

    carry = 0;
    sum = make_bigz(longer_s);

    for (i = 0; i < shorter_s; i++) {
        sum->limbs[i] = a->limbs[i] + b->limbs[i] + carry;
        /* TODO asm carry */
        carry = sum->limbs[i] < a->limbs[i];
    }
    for (; i < longer_s; i++) {
        sum->limbs[i] = longer[i] + carry;
        carry = sum->limbs[i] < longer[i];
    }

    if (carry) {
        sum->limbs =
            (unsigned int *) realloc(sum->limbs,
                                     sizeof(unsigned int) * (longer_s + 1));
        sum->size += 1;
        sum->limbs[longer_s] = carry;
    }

    return sum;
}

bigz *
bigz_usub(bigz * a, bigz * b)
{
    int borrow, i, longer_s, shorter_s;
    bigz *diff;

    longer_s = a->size;
    shorter_s = b->size;
    if (longer_s < shorter_s) {
        longer_s = b->size;
        shorter_s = a->size;
    }
    borrow = 0;
    diff = make_bigz(longer_s);

    for (i = 0; i < shorter_s; i++) {
        diff->limbs[i] = a->limbs[i] - (b->limbs[i] + borrow);
        borrow = borrow + b->limbs[i] > a->limbs[i];
    }
    if (a->size > b->size) {
        diff->limbs[i] = a->limbs[i] - borrow;
        i++;
        for (; i < longer_s; i++)
            diff->limbs[i] = a->limbs[i];
    } else {
        diff->limbs[i] = -(b->limbs[i] + borrow);
        i++;
        borrow = 1;
        for (; i < longer_s; i++)
            diff->limbs[i] = -(b->limbs[i] + borrow);
    }

    if (borrow) {
        diff->sign = 0;
        diff->limbs[0] = -diff->limbs[0];
        for (i = 1; i < longer_s; i++)
            diff->limbs[i] = -(diff->limbs[i] + 1);
    }

    /* TODO truncate leading zeros */
    return diff;
}
