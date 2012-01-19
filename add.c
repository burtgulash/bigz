#include <stdlib.h>

#include "bigz.h"

/*
 * Unsigned addition. Returns |a| + |b|.
 */
bigz *
bigz_uadd(bigz * a, bigz * b)
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
        /* TODO asm add with carry? */
        if (carry)
            carry = sum->limbs[i] <= a->limbs[i];
        else
            carry = sum->limbs[i] < a->limbs[i];
    }
    for (; i < longer_s; i++) {
        sum->limbs[i] = longer[i] + carry;
        carry = sum->limbs[i] < longer[i];
    }

    if (carry) {
        sum->limbs =
            (unsigned int *) realloc(sum->limbs,
                                     sizeof(unsigned int) * (longer_s +
                                                             1));
        sum->size += 1;
        sum->limbs[longer_s] = carry;
    }

    return (sum);
}

/*
 * Unsigned subtraction. Returns |a| - |b|.
 */
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

    /* FIXME borrow bug? */
    for (i = 0; i < shorter_s; i++) {
        diff->limbs[i] = a->limbs[i] - (b->limbs[i] + borrow);
        if (borrow)
            borrow = b->limbs[i] >= a->limbs[i];
        else
            borrow = b->limbs[i] > a->limbs[i];
    }
    if (a->size > b->size)
        for (; i < longer_s; i++) {
            diff->limbs[i] = a->limbs[i] - borrow;
            borrow = borrow > a->limbs[i];
    } else
        for (; i < longer_s; i++) {
            diff->limbs[i] = -(b->limbs[i] + borrow);
            borrow = borrow + b->limbs[i] > 0;
        }

    /* Flip sign and complement digits if a < b. */
    if (borrow) {
        diff->sign = NEGATIVE;
        diff->limbs[0] = -diff->limbs[0];
        for (i = 1; i < longer_s; i++)
            diff->limbs[i] = -(diff->limbs[i] + 1);
    }

    /* TODO truncate leading zeros */
    return (diff);
}


/*
 * Signed addition. Returns a + b.
 */
bigz *
bigz_add(bigz * a, bigz * b)
{
    bigz *sum;

    if (a->sign == b->sign) {
        sum = bigz_uadd(a, b);
        sum->sign = a->sign;
    } else {
        sum = bigz_usub(a, b);
        if (a->sign == NEGATIVE)
            sum->sign = !sum->sign;
    }

    return (sum);
}


/*
 * Signed subtraction. Returns a - b.
 */
bigz *
bigz_sub(bigz * a, bigz * b)
{
    bigz *diff;

    /* FIXME Side effect on b->sign. */
    b->sign = !b->sign;
    diff = bigz_add(a, b);
    b->sign = !b->sign;

    return (diff);
}
