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
	printf("\nTest of the function is_child:\n");
	quadrant_t	c1, c2;
	
	printf("Root quadrant q: \n");
	root (&q);
	printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
		  q.level);
	printf("q is child q: %i (expect 1)\n", is_child(&q, &q));
		  
	// Generate child quadrant c1 of q
	printf("Child quadrant c1 of q: \n");
	child(&q, &c1, 1);
	printf ("c1.x = %i, c1.y = %i, c1.z = %i, level = %i, child_id(c1) = %i\n", c1.x, c1.y, c1.z,
		  c1.level, child_id(&c1));
	printf("c1 is child of q: %i (expect 1)\n", is_child(&c1, &q));
	
	// Generate child quadrants c2 of c1
	printf("Child quadrant c2 of c1: \n");
	child(&c1, &c2, 2);
	printf ("c2.x = %i, c2.y = %i, c2.z = %i, level = %i, child_id(c2) = %i\n", c2.x, c2.y, c2.z,
		  c2.level, child_id(&c2));
		  
	// Expect 0
	printf("c2 is child of q: %i (expect 0)\n", is_child(&c2, &q));
	// Expect 1
	printf("c2 is child of c1: %i (expect 1)\n", is_child(&c2, &c1));
	// Expect -1
	printf("q is child of c1: %i (expect -1)\n", is_child(&q, &c1));

	return 0;
}

