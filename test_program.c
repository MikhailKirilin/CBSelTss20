#include "tree_based_quadrants.h"

int
main ()
{
    quadrant_t          q, ld, fd, ch1, ch2;

    root (&q);
    printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);
    if (last_descendant (&q, &ld, 1) == 0)
    /* error message will be printed by last_descendant */
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);

    //AK: prints error message
    printf("%i\n",is_sibling(&q,&ld) );

    first_descendant(&q,&fd,1);
    //True: prints 1
    printf("%i\n",is_sibling(&ld,&fd) );

    child(&fd,&ch1,2);
    child(&ld,&ch2,6);
    //False: prints 0
    printf("%i\n",is_sibling(&ch1,&ch2) );

    return 0;
}
