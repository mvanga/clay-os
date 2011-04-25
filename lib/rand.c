#include <clay/types.h>

static unsigned int seed=1;

int rand_r(unsigned int* seed);

int rand(void) {
  return rand_r(&seed);
}

void srand(unsigned int i) { seed=i; }

int random(void) __attribute__((alias("rand")));
void srandom(unsigned int i) __attribute__((alias("srand")));

/* Knuth's TAOCP section 3.6 */
#define	M	((1U<<31) -1)
#define	A	48271
#define	Q	44488		// M/A
#define	R	3399		// M%A; R < Q !!!

int rand_r(unsigned int* seed)
{   s32 X;

    X = *seed;
    X = A*(X%Q) - R * (s32) (X/Q);
    if (X < 0)
	X += M;

    *seed = X;
    return X;
}
