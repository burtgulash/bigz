#ifndef BIGZ_H
#define BIGZ_H

typedef struct {
	int size, sign;
	unsigned int *limbs;
} bigz;

bigz * make_bigz (int size);
void free_bigz (bigz *n);

bigz * bigz_uadd(bigz * a, bigz * b);
bigz * bigz_usub(bigz *a, bigz *b);

int cmp(bigz *a, bigz *b);

#endif
