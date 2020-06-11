#include "tree_based_quadrants.h"

int
main ()
{
  quadrant_t          q, ld;

  root (&q);
  printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);
  if (last_descendant (&q, &ld, 1) == 0)
    /* error message will be printed by last_descendant */
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);
  
  
	//GM
	printf("\nTest of the function child_id:\n");
	quadrant_t	c;
	printf("Root quadrant q: \n");
	root (&q);
	printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
		  q.level);
	printf("Child quadrants c with child_ids i=0,...,8:\n");
	// Generate child quadrants c with child_ids i=0,...,8 and print their coordinates, level and child_id
	for (int i = 0; i <= 8; i++) {
		child(&q, &c, i);
		if (i == 8)
			printf("Expect error message for child_id(c) = 8:\n");
		// Expect error message in last oputput line for i=8
		printf ("c.x = %i, c.y = %i, c.z = %i, level = %i, child_id(c) = %i\n", c.x, c.y, c.z,
            c.level, child_id(&c));
	}
	return 0;
}

