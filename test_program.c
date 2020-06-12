#include "tree_based_quadrants.h"

int
main ()
{
  quadrant_t          q, ld,fd, s1, s2, s3;;

  root (&q);
  printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);
  if (last_descendant (&q, &ld, 1) == 0)
    /* error message will be printed by last_descendant */
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);
  if (first_descendant(&ld, &fd, 3) == 0)
	  printf("fd.x = %i, fd.y = %i, fd.z = %i, level = %i\n", fd.x, fd.y, fd.z, fd.level);
  if (sibling(&ld, &s1, 0) == 0) 
	  printf("s1.x = %i, s1.y = %i, s1.z = %i, level = %i, sibling_id = 0\n", s1.x, s1.y, s1.z, s1.level);
  if (sibling(&ld, &s2, 1) == 0)
	  printf("s2.x = %i, s2.y = %i, s2.z = %i, level = %i, sibling_id = 1\n", s2.x, s2.y, s2.z, s2.level);
  if (sibling(&ld, &s3, 7) == 0)
	  printf("s3.x = %i, s3.y = %i, s3.z = %i, level = %i, sibling_id = 7\n", s3.x, s3.y, s3.z, s3.level);

  return 0;
}
