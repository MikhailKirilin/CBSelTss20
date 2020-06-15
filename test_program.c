#include "tree_based_quadrants.h"

void
test_ancestor ()
{
  quadrant_t          r, ld, fd, ld_anc, fd_anc;

  root (&r);

  last_descendant (&r, &ld, 4);
  ancestor (&ld, 2, &ld_anc);

  first_descendant (&r, &fd, 4);
  ancestor (&fd, 2, &fd_anc);

  if (is_ancestor (&r, &fd_anc) && is_ancestor (&r, &ld_anc)) {
    printf ("The root quadrant is ancestor of ancestors of the first "
            "and last descendants of the root\n");
  }
  else {
    printf ("something went wrong!\n");
  }

  if (!is_ancestor (&ld_anc, &fd_anc) && !is_ancestor (&ld_anc, &fd_anc)) {
    printf ("Elements on the same level are only ancestors of each other "
            "if they are the same\n");
  }
  else {
    printf ("something went wrong!\n");
  }
}

int
main ()
{
  quadrant_t          q, ld, ch, r, sib, fd, s1, s2, s3, siblingparent,
    siblingchild;
  quadrant_t          children[8];
  int                 flag = 1;

  //TG: root and last_descendant
  printf ("TG: root and last_descendant\n BEGIN:\n");
  root (&q);
  printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);
  if (last_descendant (&q, &ld, 1) == 0)
    /* error message will be printed by last_descendant */
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);
  printf (" END\n\n");

  //GM: child_id
  printf ("GM: child_id\n BEGIN:\n");
  quadrant_t          c;
  printf ("Root quadrant q: \n");
  root (&q);
  printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);
  printf ("Child quadrants c with child_ids i=0,...,8:\n");
  // Generate child quadrants c with child_ids i=0,...,8 and print their
  // coordinates, level and child_id
  for (int i = 0; i <= 8; i++) {
    child (&q, &c, i);
    // Expect error message in last oputput line for i=8
    if (i == 8)
      printf ("Expect error message for child_id(c) = 8:\n");
    printf ("c.x = %i, c.y = %i, c.z = %i, level = %i, child_id(c) = %i\n",
            c.x, c.y, c.z, c.level, child_id (&c));
  }
  printf (" END\n\n");

  //AK
  printf ("AK: child\n BEGIN:\n");
  root (&q);
  child (&q, &ld, 7);
  child (&ld, &ch, 7);
  printf ("ch.x = %i, ch.y = %i, ch.z = %i, ch.level = %i \n", ch.x, ch.y,
          ch.z, ch.level);
  last_descendant (&q, &ld, 2);
  //This should be the same quadrant, in future is_equal can be used
  printf ("ld.x = %i, ld.y = %i, ld.z = %i, ld.level = %i\n", ld.x, ld.y,
          ld.z, ld.level);
  printf (" END\n\n");

  //GC: parent
  printf ("GC: parent\n BEGIN:\n");
  //test of child and sibling functions
  // we assign root and its first descendant at level 1
  root (&r);
  // we assign the children
  for (int i = 0; i < 8; i++) {
    child (&r, &children[i], i);
  }
  // we check that all the children of the root are siblings
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++) {
      if (i == j)
        continue;
      // we compute the j-th sibling of the i-th child 
      sibling (&children[i], &sib, j);
      // we compute the i-th sibling of the the j-th sibling of th i-th child
      sibling (&sib, &q, i);
      // wh check if it is the same of the i-th child of the root
      if (children[i].x - q.x != 0
          || children[i].y - q.y != 0 || children[i].z - q.z != 0) {
        printf ("Error: the %d-th child of the root is has not the %d-th "
                "chlid of the root as %d-sibling\n", i, j, j);
        flag = 0;
        break;
      }

    }
  if (flag)
    printf ("All good: ad expected the i-th child of the root "
            "is has the j-thchlid of the root as j-sibling for any i and j\n");
  printf (" END\n\n");

  //JV: sibling and first_descendant
  printf ("JV: sibling and first_descendant\n BEGIN:\n");
  root (&q);
  printf ("q.x = %i, q.y = %i, q.z = %i, level = %i\n", q.x, q.y, q.z,
          q.level);
  if (last_descendant (&q, &ld, 1) == 0)
    /* error message will be printed by last_descendant */
    printf ("ld.x = %i, ld.y = %i, ld.z = %i, level = %i\n", ld.x, ld.y, ld.z,
            ld.level);

  /* JV  testing first descendant and sibling */
  if (first_descendant (&ld, &fd, 3) == 0)
    printf ("fd.x = %i, fd.y = %i, fd.z = %i, level = %i\n", fd.x, fd.y, fd.z,
            fd.level);
  if (sibling (&ld, &s1, 0) == 0)
    printf ("s1.x = %i, s1.y = %i, s1.z = %i, level = %i, sibling_id = 0\n",
            s1.x, s1.y, s1.z, s1.level);
  if (sibling (&ld, &s2, 1) == 0)
    printf ("s2.x = %i, s2.y = %i, s2.z = %i, level = %i, sibling_id = 1\n",
            s2.x, s2.y, s2.z, s2.level);
  /* checking if child(parent(fd),3) = sibling(fd,3) */
  if (sibling (&fd, &s3, 3) == 0)
    printf ("s3.x = %i, s3.y = %i, s3.z = %i, level = %i, sibling_id = 7\n",
            s3.x, s3.y, s3.z, s3.level);
  if (parent (&fd, &siblingparent) == 0)
    printf ("sp.x = %i, sp.y = %i, sp.z = %i, level = %i, \n",
            siblingparent.x, siblingparent.y, siblingparent.z,
            siblingparent.level);
  if (child (&siblingparent, &siblingchild, 3) == 0)
    printf ("sc.x = %i, sc.y = %i, sc.z = %i, level = %i, \n", siblingchild.x,
            siblingchild.y, siblingchild.z, siblingchild.level);
#if 0
  if (is_equal (s3, siblingchild))
    printf ("this test was succesful");
  else
    printf ("something went wrong");
#endif
  printf (" END\n\n");

  /* LD */
  printf ("LD: ancestor\n BEGIN:\n");
  test_ancestor ();
  printf (" END\n\n");

  return 0;
}
