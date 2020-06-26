#include "tree_based_quadrants.h"

int
main ()
{
  //OP: test is_equal

  quadrant_t          q, ld, r;

  root (&q); 
  child (&q, &ld, 3);
  child (&q, &r, 3);
  printf ("OP: is_equal\n BEGIN:\n");
  printf ("test of reflexivity of:\n");
  if (is_equal(&q,&q) && is_equal(&ld, &ld) && is_equal(&r, &r)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("test of equality of two instances of third child of root:\n");
  if (is_equal(&ld,&r)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf("test of inequality of root and instance of third child of root:\n");
  if (!is_equal(&q,&ld)) {
    printf ("was successful\n");
  } 
  else {
    printf ("ended in ERROR\n");
  }
  printf (" END\n\n");

  return 0;
}
