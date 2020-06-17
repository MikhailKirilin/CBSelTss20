#include "tree_based_quadrants.h"

int
main ()
{
  //TG: test root

  quadrant_t          q;

  printf ("TG: root and last_descendant\n BEGIN:\n");
  /* test the root function by printing the root coordinates and level */
  root (&q);
  printf ("The root quadrant q:\n");
  printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);

  return 0;
}
