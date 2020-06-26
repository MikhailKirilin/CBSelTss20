#include "tree_based_quadrants.h"

int
main ()
{
  //OP: test is_strict_ancestor

  quadrant_t          r, c, gc, a, ir;

  root (&r);
  root(&ir);
  ir.level = 20;
  child (&r, &c, 3);
  child (&c, &gc, 1);
  ancestor(&gc, 1, &a);
  printf ("OP: is_strict_ancestor\n BEGIN:\n");
  printf ("test of nonreflexivity:\n");
  if (!is_strict_ancestor(&r,&r) && !is_strict_ancestor(&c, &c) && !is_strict_ancestor(&gc, &gc)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("test root as strict ancestor of child:\n");
  if (is_strict_ancestor(&r,&c)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("test invalid root as strict ancestor of child:\n");
  if (!check_return_value (is_strict_ancestor(&ir,&c), 0)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("test child as no strict ancestor of root\n");
  if (!is_strict_ancestor(&c,&r)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("test root as strict ancestor of grandchild\n");
  if (is_strict_ancestor(&r,&gc)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("level 1 ancestor of grandchild");
  if(is_equal(&a, &c)){
    printf(" equal to child of root\n");
  }
  else{
    printf(" unequal to child of root ERROR\n");
  }
  printf("test level 1 ancestor as strict ancestor of grandchild\n");
  if (is_strict_ancestor(&r,&gc)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf (" END\n\n");

  return 0;
}
