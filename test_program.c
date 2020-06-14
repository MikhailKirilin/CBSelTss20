#include "tree_based_quadrants.h"

int
main ()
{
  quadrant_t          r, q, sib;
  quadrant_t          children[8];
  //test of child and sibling functions
  int                 flag = 1;
  // we assign root and its first descendant at level 1
  root (&r);
  // we assign the children
  for (int i = 0; i < 8; i++) {
    child(&r, &children[i], i);
  }
  // we check that all the children of the root are siblings
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (i == j) continue;
      // we compute the j-th sibling of the i-th child 
      sibling(&children[i], &sib, j);
      // we compute the i-th sibling of the the j-th sibling of th i-th child
       sibling(&sib, &q, i);
      // wh check if it is the same of the i-th child of the root
      if ( children[i].x - q.x != 0 
        || children[i].y - q.y != 0 
        || children[i].z - q.z != 0 ) {
        printf("Error: the %d-th child of the root is has not the %d-th chlid of the root as %d-sibling\n",
                i, j, j);
        flag = 0;
        break;
        }
      
    }

  if (flag)
    printf( "All good: ad expected the i-th child of the root is has the j-th chlid of the root as j-sibling for any i and j\n");
  return 0;
}
