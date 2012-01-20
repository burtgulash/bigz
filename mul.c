#include "bigz.h"


/*
 * Unsigned multiplication. Returns |a * b|
 */
bigz *
bigz_umul(bigz * a, bigz * b)
{
    int i, j;
    unsigned int sum_carry, carry, mul_carry;
    unsigned int tmp, c0, c1, c2, c3;   /* storage for partial products */
    bigz *prod;

    if (a->size < b->size) {
        prod = a;
        a = b;
        b = prod;
    }
    prod = make_bigz(a->size + b->size);

    for (i = 0; i < b->size; i++) {
        sum_carry = mul_carry = 0;

#define HALF (sizeof(unsigned int) * 8 / 2)
#define HALF_INT (((unsigned int) ~0) >> HALF)
#define tohi(x) ((x) << HALF)
#define hi(x) ((x) >> HALF)
#define lo(x) (HALF_INT & (x))

        for (j = 0; j < a->size; j++) {
            c0 = lo(b->limbs[i]) * lo(a->limbs[j]);
            c1 = hi(b->limbs[i]) * lo(a->limbs[j]);
            c2 = lo(b->limbs[i]) * hi(a->limbs[j]);
            c3 = hi(b->limbs[i]) * hi(a->limbs[j]);

            tmp = c0 + tohi(c1) + tohi(c2) + mul_carry;
            carry = tmp < mul_carry;

            carry += lo(c1) + lo(c2) + hi(c0) >> HALF;
            mul_carry = c3 + hi(c1) + hi(c2) + carry;

            prod->limbs[i + j] += tmp + sum_carry;
            if (sum_carry)
                sum_carry = prod->limbs[i + j] <= tmp;
            else
                sum_carry = prod->limbs[i + j] < tmp;
        }

#undef hi
#undef lo
#undef HALF_INT
#undef HALF

        prod->limbs[i + j] += mul_carry + sum_carry;

        /* 
         * Last digit is always added to zero. Last digit is always less
         * than MAX digit, therefore carry won't propagate to the next digit.
         * No overflow handling is needed.
         */
    }

    return (prod);
}


/*
 * Signed multiplication. Returns a * b.
 */
bigz *
bigz_mul(bigz * a, bigz * b)
{
    bigz *prod;

    prod = bigz_umul(a, b);
    if (a->sign != b->sign)
        prod->sign = NEGATIVE;

    return prod;
}
