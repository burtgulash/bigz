#include "bigz.h"


bigz *
bigz_umul(bigz * a, bigz * b)
{
    int i, j;
    unsigned int main_add_carry, add_carry, mul_carry;
    unsigned int cross_prod;
    unsigned int tmp;
    bigz *prod;

    if (a->size < b->size) {
        prod = a;
        a = b;
        b = prod;
    }
    prod = make_bigz(a->size + b->size);

    for (i = 0; i < b->size; i++) {
        main_add_carry = mul_carry = 0;

        for (j = 0; j < a->size; j++) {
            tmp = (b->limbs[i] * a->limbs[j]) + mul_carry;
            add_carry = tmp < mul_carry;

#define HALF (sizeof(unsigned int) * 8 / 2)
#define HALF_INT (((unsigned int) ~0) >> HALF)
#define hi(x) ((x) >> HALF)
#define lo(x) (HALF_INT & (x))
            cross_prod = hi(hi(b->limbs[i]) * lo(a->limbs[j])) +
                hi(lo(b->limbs[i]) * hi(a->limbs[j]));
            add_carry += cross_prod >= HALF_INT;
            mul_carry = hi(b->limbs[i]) * hi(a->limbs[j]) +
                cross_prod + add_carry;
#undef hi
#undef lo
#undef HALF_INT
#undef HALF

            prod->limbs[i + j] += tmp + main_add_carry;
            if (main_add_carry)
                main_add_carry = prod->limbs[i + j] <= tmp;
            else
                main_add_carry = prod->limbs[i + j] < tmp;
        }

        prod->limbs[i + j] += mul_carry + main_add_carry;

        /* 
         * Last digit is always added to zero. Last digit is always less
         * than MAX digit, therefore carry won't propagate to the next digit.
         * No overflow handling is needed.
         */
    }

    return (prod);
}
