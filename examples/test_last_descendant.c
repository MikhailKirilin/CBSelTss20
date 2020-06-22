#include "tree_based_quadrants.h"

int
main ()
{
  //TG: test last_descendant

  quadrant_t          q, ld, r;

  root (&q);
  /* print an example of a last descendant */
  if (last_descendant (&q, &ld, 1) == 0) {
    /* error message will be printed by last_descendant */
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);

    /* check parent of the last descendant on level 1 */
    if (parent (&ld, &r) == 0) {
        if (!(is_equal (&q, &r)))
          printf ("Error: parent of the last descendant on level one of the \
                 root should be the root.\n");
    }
  }

  /* check the child id of a last descendant */
  if (last_descendant (&ld, &ld, 4) == 0) {
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);
    if (sibling (&ld, &r, 7) == 0) {
      if (!(is_equal (&ld, &r)))
          printf
            ("Error: the child id of the last descendant should be 7.\n");
    }
  }

  return 0;
}
