#include "tree_based_quadrants.h"

void test_ancestor(){
    quadrant_t r, ld, fd, ld_anc, fd_anc;

    root(&r);

    last_descendant(&r, &ld, 4);
    ancestor(&ld, 2, &ld_anc);

    first_descendant(&r,&fd,4);
    ancestor(&fd, 2, &fd_anc);

    if(is_ancestor(&r, &fd_anc) && is_ancestor(&r , &ld_anc)){
        printf("The root quadrant is ancestor of ancestors of the first and last descendants of the root\n");
    }else{
        printf("something went wrong!\n");
    }   

    if(!is_ancestor(&ld_anc,&fd_anc) && !is_ancestor(&ld_anc,&fd_anc)){
        printf("Elements on the same level are only ancestors of each other if they are the same\n");
    }else{
        printf("something went wrong!\n");
    }
}

int
main ()
{
    quadrant_t          q, ld, ch;

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


    /*LD*/
    test_ancestor();

  return 0;
}