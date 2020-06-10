#include "tree_based_quadrants.h"

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


  return 0;
}
