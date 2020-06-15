#include "tree_based_quadrants.h"

int
is_valid (const quadrant_t * q)
{
  return
    (q->level >= 0 && q->level <= MAXLEVEL) &&
    ((q->x & (QUADRANT_LEN (q->level) - 1)) == 0) &&
    ((q->y & (QUADRANT_LEN (q->level) - 1)) == 0) &&
    ((q->z & (QUADRANT_LEN (q->level) - 1)) == 0);
}

int 
child_id (const quadrant_t *q) 
{
	if(is_valid(q)) {
		// length of the quadrant at level q->level
		int h = QUADRANT_LEN(q->level);
		// return variable
		int res = 0;
		
		// Check wheter the coordinates of q are even or odd multiples of the quadrant_length 
		// and add up the corresponding powers of 2
		res += (q->x & h ? 1 : 0);
		res += ((q->y & h ? 1 : 0) << 1);
		res += ((q->z & h ? 1 : 0) << 2);
		
		// Check whether the return value is valid
		if (res >= 0 && res <= 7)
			return res;
		else {
			printf ("child_id: the return value does not lie between 0 (inclusive) and 7 (inclusive).\n");
			return -1;
		}
	}
	else {
		printf ("child_id: the input quadrant has to be valid.\n");
		return -1;
	}
}

int
child (const quadrant_t * q, quadrant_t * child_quadrant, int child_id)
{
  child_quadrant->level = q->level + 1;

  child_quadrant->x =
    q->x + (child_id & 1 ? QUADRANT_LEN (child_quadrant->level) : 0);
  child_quadrant->y =
    q->y + (child_id & 2 ? QUADRANT_LEN (child_quadrant->level) : 0);
  child_quadrant->z =
    q->z + (child_id & 4 ? QUADRANT_LEN (child_quadrant->level) : 0);

  return 0;
}

int
parent (const quadrant_t * q, quadrant_t * parent_quadrant)
{
  if (q->level == 0) {
    printf ("The root has no parent quadrant");
    return -1;
  }
  // level of the parent decreases by 1
  parent_quadrant->level = q->level - 1;
  // we compute the size
  int                 h = QUADRANT_LEN (q->level);
  // compute parent coordinates
  parent_quadrant->x = q->x & ~h;
  parent_quadrant->y = q->y & ~h;
  parent_quadrant->z = q->z & ~h;

  return 0;
}

void
root (quadrant_t * q)
{
  q->level = 0;
  q->x = q->y = q->z = 0;
}

int
sibling (const quadrant_t * q, quadrant_t * sibling_quadrant, int sibling_id)
{

  if (!is_valid (q)) {
    printf ("sibling: the input quadrant has to be valid.\n");
    return -1;
  }

  if (sibling_id < 0 || sibling_id > 7) {
    printf ("sibling: sibling_id should lie between 0 (included) \
        and 7 (included).\n");
    return -1;
  }

  sibling_quadrant->level = q->level;
  // we compute the size
  int                 h = QUADRANT_LEN (q->level);
  // compute parent coordinates
  sibling_quadrant->x = (sibling_id & 1) ? (q->x | h) : (q->x & ~h);
  sibling_quadrant->y = (sibling_id & 2) ? (q->y | h) : (q->y & ~h);
  sibling_quadrant->z = (sibling_id & 4) ? (q->z | h) : (q->z & ~h);

  return 0;
}

int
ancestor (const quadrant_t * q, int level,quadrant_t * ancestor_quadrant)
{
  qcoord_t        mask;

  if (!is_valid (q)) {
    printf ("ancestor: the input quadrant has to be valid.\n");
    return -1;
  }

  if((int) q->level < level || level < 0) {
    printf("ancestor: level should be between 0 and quadrant level");
    return -1;
  }
  mask = ~(QUADRANT_LEN(level) - 1);

  ancestor_quadrant->level = level;
  ancestor_quadrant->x = q->x & mask;
  ancestor_quadrant->y = q->y & mask;
  ancestor_quadrant->z = q->z & mask;

  return 0;
}

int
is_ancestor (const quadrant_t * q, const quadrant_t * r)
{
  qcoord_t          mask;

  if (!is_valid (q) || !is_valid (r)) {
    printf ("is_ancestor: the input quadrants have to be valid.\n");
    return -1;
  }

  mask = ~(QUADRANT_LEN(q->level) - 1);
  return (q->level <= r->level) && !((q->x ^ r->x) & mask)
                                && !((q->y ^ r->y) & mask)
                                && !((q->z ^ r->z) & mask);
}

int
first_descendant (const quadrant_t * q, quadrant_t * first_descendant,
                  int level)
{

  if (!is_valid (q)) {
    printf ("first_descendant: the input quadrant has to be valid.\n");
    return -1;
  }

  if ((int) q->level > level || level >= MAXLEVEL) {
    printf
      ("first_descendant: level should lie between quadrant level (included) \
        and MAXLEVEL (excluded).\n");
    return -1;
  }

  first_descendant->x = q->x;
  first_descendant->y = q->y;
  first_descendant->z = q->z;

  first_descendant->level = (int8_t) level;

  return 0;
}

int
last_descendant (const quadrant_t * q, quadrant_t * last_descendant,
                 int level)
{
  qcoord_t            shift;

  if (!is_valid (q)) {
    printf ("last_descendant: the input quadrant has to be valid.\n");
    return -1;
  }

  if (!((int) q->level <= level && level < MAXLEVEL)) {
    printf
      ("last_descendant: level should lie between quadrant level (included) \
        and MAXLEVEL (excluded).\n");
    return -1;
  }

  shift = QUADRANT_LEN (q->level) - QUADRANT_LEN (level);

  last_descendant->x = q->x + shift;
  last_descendant->y = q->y + shift;
  last_descendant->z = q->z + shift;

  last_descendant->level = (int8_t) level;

  return 0;
}
