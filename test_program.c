#include "tree_based_quadrants.h"

int
main ()
{
  quadrant_t          q;

  root (&q);
  printf("is_valid(q) = %i\n", is_valid(&q));


  return 0;
}
