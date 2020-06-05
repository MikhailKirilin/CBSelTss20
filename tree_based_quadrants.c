#include "tree_based_quadrants.h"

void
root (quadrant_t * q)
{
  q->level = 0;
  q->x = q->y = q->z = 0;
}

void
last_descendant (const quadrant_t * q, quadrant_t * last_descendant,
                 int level)
{
  qcoord_t            shift;

#if 0
  if (!is_valid (q)) {
    printf ("last_descendant: the input quadrant has to be valid.\n");
    return;
  }
#endif
  if ((int) q->level > level || level >= MAXLEVEL) {
    printf
      ("last_descendant: level should lie between quadrant level (included) \
        and MAXLEVEL (excluded).\n");
    return;
  }

  shift = QUADRANT_LEN (q->level) - QUADRANT_LEN (level);

  last_descendant->x = q->x + shift;
  last_descendant->y = q->y + shift;
  last_descendant->z = q->z + shift;

  last_descendant->level = (int8_t) level;
}
