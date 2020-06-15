#include "tree_based_quadrants.h"

int
main ()
{
    quadrant_t          q, ld, ch, r, sib;
    quadrant_t          children[8];
    int                 flag = 1;

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
		// Expect error message in last oputput line for i=8
		if (i == 8)
			printf("Expect error message for child_id(c) = 8:\n");
		printf ("c.x = %i, c.y = %i, c.z = %i, level = %i, child_id(c) = %i\n", c.x, c.y, c.z,
            c.level, child_id(&c));
	}

    //AK
    root(&q);
    child(&q,&ld,7);
    child(&ld,&ch,7);
    printf("ch.x = %i, ch.y = %i, ch.z = %i, ch.level = %i \n", ch.x, ch.y,
        ch.z, ch.level);
    last_descendant(&q,&ld,2);
    //This should be the same quadrant, in future is_equal can be used
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, ld.level = %i\n", ld.x, ld.y,
        ld.z, ld.level);

  //test of child and sibling functions
  // we assign root and its first descendant at level 1
  root (&r);
  // we assign the children
  for (int i = 0; i < 8; i++) {
    child(&r, &children[i], i);
  }
  // we check that all the children of the root are siblings
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (i == j) continue;
      // we compute the j-th sibling of the i-th child 
      sibling(&children[i], &sib, j);
      // we compute the i-th sibling of the the j-th sibling of th i-th child
       sibling(&sib, &q, i);
      // wh check if it is the same of the i-th child of the root
      if ( children[i].x - q.x != 0 
        || children[i].y - q.y != 0 
        || children[i].z - q.z != 0 ) {
        printf("Error: the %d-th child of the root is has not the %d-th chlid of the root as %d-sibling\n",
                i, j, j);
        flag = 0;
        break;
        }
      
    }

  if (flag)
    printf( "All good: ad expected the i-th child of the root is has the j-th chlid of the root as j-sibling for any i and j\n");
  return 0;
}

