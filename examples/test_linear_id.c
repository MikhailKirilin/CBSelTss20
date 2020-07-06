#include "tree_based_quadrants.h"

int
main ()
{
	quadrant_t q, r, test;
	quadrant_lin L;
	root(&r);
	printf("the root (%i, %i, %i) \n", r.x, r.y, r.z);

	child(&r, &q, 2);
	printf("has child (%i, %i, %i)\n", q.x, q.y, q.z);

	linear_id(&q, &L);
	printf("with linear index %li \n", L.I);
	linear_id_inv(&L, &test);
	printf("whose inverse is (%i, %i, %i) \n", test.x, test.y, test.z);

	if (is_equal(&test, &q) > 0) printf("so it's all good\n");

	else printf("error: linear_index_inv not inverse of linear_id\n");
	return 0;
}