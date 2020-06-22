#include "tree_based_quadrants.h"

int
main ()
{
  quadrant_t          	par,fd, q, r;
  int 					lvl = rand() % MAXLEVEL;
  int 					i = rand() % 8;
  // assign the root
  root (&r);
  // compute first descendant of the root at random level
  first_descendant (&r, &fd, lvl);
  // compute a random sibling
  sibling (&fd, &q, i);
  // compute the parent
  parent (&q, &par);
  if (!is_parent(&par, &q))
  	printf   ("is_parent: something is wrong!\n");
  else 
  	printf 	("the parent of (%i, %i, %i) at level %i is (%i, %i, %i) at level %i\n",
  			q.x, q.y, q.z, q.level, 
        	par.x, par.y, par.z, par.level );
  return 0;
}
