#include "bigz.h"

int
cmp(bigz *a, bigz *b)
{
	int i;

	if (a->size < b->size) {
		for (i = 0; i < a->size; i++)
			if (a->limbs[i] != b->limbs[i])
				return 0;
		for (; i < b->size; i++)
			if (b->limbs[i])
				return 0;
	} else {
		for (i = 0; i < b->size; i++)
			if (a->limbs[i] != b->limbs[i])
				return 0;
		for (; i < a->size; i++)
			if (a->limbs[i])
				return 0;
	}

	return 1;
}
