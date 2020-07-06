#include "tree_based_quadrants.h"

int
main ()
{
  //TG: test last_descendant

  quadrant_t          r, c1, c2, c3, sm_ancestor;
  quadrant_lin		sm_ancestor_lin_id, c1_lin_id;

  root (&r);
  child (&r, &c1, 1);
  child (&c1, &c2, 0);
  child (&c1, &c3, 1);
  
  smallest_ancestor(&c2, &c3, &sm_ancestor);
  linear_id(&sm_ancestor, &sm_ancestor_lin_id);
  linear_id(&c1, &c1_lin_id);
  printf("c1_lin_id = %i\n", c1_lin_id.I);
  printf("smallest_ancestor_lin_id = %i", sm_ancestor_lin_id.I);
  
  return 0;
}