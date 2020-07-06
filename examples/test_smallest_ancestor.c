#include "tree_based_quadrants.h"

int
main ()
{
  //TG: test last_descendant

  quadrant_t          r, c1, c2, c3, c4, sm_ancestor;
  quadrant_lin		ancestor_lin_id, dummy;

  root (&r);
  child (&r, &c1, 1);
  child (&r, &c2, 0);
  child (&c1, &c3, 0);
  child (&c1, &c4, 1);
  
  smallest_ancestor(&c3, &c4, &sm_ancestor);
  linear_id(&sm_ancestor, &ancestor_lin_id);
  linear_id(&c1, &dummy);
  printf("dummy_lin_id = %i\n", dummy.I);
  printf("smallest_ancestor_lin_id = %i", ancestor_lin_id.I);
  
  return 0;
}