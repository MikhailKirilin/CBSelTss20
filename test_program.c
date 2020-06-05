#include "tree_based_quadrants.h"

int main () {
	quadrant_t q, ld;
	
	root (&q);
	printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z, q.level);
	last_descendant (&q, &ld, 1);
	printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z, ld.level);

	return 0;
}
