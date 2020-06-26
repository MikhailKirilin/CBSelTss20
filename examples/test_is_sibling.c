#include "tree_based_quadrants.h"

int
main ()
{
  quadrant_t          q, ld, fd, ch1, ch2;

  root (&q);
  
  printf ("AK: is_sibling\n BEGIN:\n");

  if (last_descendant (&q, &ld, 1) == 0) {
    //AK: prints 0
    printf("%i\n",is_sibling(&q,&ld) );

    first_descendant(&q,&fd,1);
    //True: prints 1
    printf("%i\n",is_sibling(&ld,&fd) );

    child(&fd,&ch1,2);
    child(&ld,&ch2,6);
    //False: prints 0
    printf("%i\n",is_sibling(&ch1,&ch2));
  }
  printf (" END\n\n");
  return 0;
}
