#include "tree_based_quadrants.h"

int check_return_value (int return_value, int8_t stop)
{
  if (return_value == -1) {
    if (stop)
      abort();
    else {
      printf ("Warning: A function returned the error value -1 but the programm was not aborted.\n");
      return 0;
    }
  }
  return return_value;
}

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
is_equal (const quadrant_t * q, const quadrant_t * r)
{
  if (is_valid (q) && is_valid (r)) {
    return (q->level == r->level) && (q->x == r->x)
      && (q->y == r->y)
      && (q->z == r->z);
  }
  else {
    printf ("is_equal: the input quadrants have to be valid.\n");
    return -1;
  }
}

int
child_id (const quadrant_t * q)
{
  if (is_valid (q)) {
    // length of the quadrant at level q->level
    int                 h = QUADRANT_LEN (q->level);
    // return variable
    int                 res = 0;

    // Check whether the coordinates of q are even or odd multiples
    // of the quadrant_length and add up the corresponding powers of 2
    res += (q->x & h ? 1 : 0);
    res += ((q->y & h ? 1 : 0) << 1);
    res += ((q->z & h ? 1 : 0) << 2);

    // Check whether the return value is valid
    if (res >= 0 && res <= 7)
      return res;
    else {
      printf ("child_id: the return value does not lie between \
          0 (inclusive) and 7 (inclusive).\n");
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
  if (!is_valid (q)) {
    printf ("child: The input quadrant q is not valid.\n");
    return -1;
  }
  if (child_id < 0 || child_id > 7) {
    printf ("child: The child_id %i is not valid "
            "(needs to be between 0 (included) and 7 (included)).\n",
            child_id);
    return -1;
  }
  if (q->level == MAXLEVEL) {
    printf ("child: The level of the input quadrant is already MAXLEVEL\n");
    return -1;
  }

  child_quadrant->level = q->level + 1;

  int                 shift = QUADRANT_LEN (child_quadrant->level);

  child_quadrant->x = q->x + (child_id & 1 ? shift : 0);

  child_quadrant->y = q->y + (child_id & 2 ? shift : 0);

  child_quadrant->z = q->z + (child_id & 4 ? shift : 0);

  //I was asked for this check, in case we change some logic later on.
  if (!is_valid (child_quadrant)) {
    printf ("child: The output quadrant child_quadrant is not valid.\n");
    return -1;
  }

  return 0;
}

// Checks whether q is a child of r
int                 
is_child (const quadrant_t * q, const quadrant_t * r)
{
	qcoord_t        mask;
	
	if(is_valid(q) && is_valid(r)) {
		if (q->level > 0) {
		mask = ~(QUADRANT_LEN(r->level) - 1);
		// checks whether r is an ancestor of q and whether q has equal level as r or is one level below r
		return (q->level == r->level || q->level == r->level + 1) && !((q->x ^ r->x) & mask)
										  && !((q->y ^ r->y) & mask)
										  && !((q->z ^ r->z) & mask);
		}
		// if q has level 0 so must r
		else 
			return (r->level == 0);
	}
	else {
		printf ("is_child: input quadrants have to be valid.\n");
		return -1;
	}
}



int
parent (const quadrant_t * q, quadrant_t * parent_quadrant)
{
  if (!is_valid (q)) {
    printf ("parent: the input quadrant is not valid.\n");
    return -1;
  }

  if (q->level <= 0) {
    printf ("The root has no parent quadrant.\n");
    return -1;
  }
  // level of the parent decreases by 1
  parent_quadrant->level = q->level - 1;
  // we compute the size and its bitwise negation
  int                 h = QUADRANT_LEN (q->level);
  int                 not_h = ~h;
  // compute parent coordinates
  parent_quadrant->x = q->x & not_h;
  parent_quadrant->y = q->y & not_h;
  parent_quadrant->z = q->z & not_h;

  if (!is_valid (parent_quadrant)) {
    printf ("parent: the output quadrant is not valid.\n");
    return -1;
  }

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
        /** we compute the size */
  int                 h = (int) QUADRANT_LEN (q->level);

  if (!is_valid (q)) {
    printf ("sibling: the input quadrant has to be valid.\n");
    return -1;
  }

  if (sibling_id < 0 || sibling_id > 7) {
    printf ("sibling: sibling_id should lie between 0 (included) \
        and 7 (included).\n");
    return -1;
  }

  if (q->level == 0 && sibling_id < 0) {
    printf ("sibling: the root has no real siblings");
    return -1;
  }

  sibling_quadrant->level = q->level;
  /** compute parent coordinates */
  sibling_quadrant->x = (sibling_id & 1) ? (q->x | h) : (q->x & ~h);
  sibling_quadrant->y = (sibling_id & 2) ? (q->y | h) : (q->y & ~h);
  sibling_quadrant->z = (sibling_id & 4) ? (q->z | h) : (q->z & ~h);

  if (!is_valid (sibling_quadrant)) {
    printf ("sibling: the output quadrant is not valid.\n");
    return -1;
  }

  return 0;
}

int is_sibling (const quadrant_t * q, const quadrant_t * r)
{
  if(!is_valid(q) || !is_valid(r) )
  {
    printf("is_sibling: the input quadrants have to be valid. \n" );
    return -1;
  }
   //checking for level guarantees that nothing weird happens with mask
  if(!(q->level == r->level))
  {
    //printf("is_sibling: the input quadrants have to have the same level.\n" );
    return 0;
  }

  qcoord_t mask = ~QUADRANT_LEN(q->level);

  return !((q->x ^ r->x) & mask) && !((q->y ^ r->y) & mask)
                                && !((q->z ^ r->z) & mask);

}

int
ancestor (const quadrant_t * q, int level, quadrant_t * ancestor_quadrant)
{
  qcoord_t            mask;

  if (is_valid (q)) {
    if (level <= (int) q->level || level >= 0) {
      mask = ~(QUADRANT_LEN (level) - 1);

      ancestor_quadrant->level = level;
      ancestor_quadrant->x = q->x & mask;
      ancestor_quadrant->y = q->y & mask;
      ancestor_quadrant->z = q->z & mask;

    }
    else {
      printf ("ancestor: level should be between 0 and quadrant level");
      return -1;
    }

  }
  else {
    printf ("ancestor: the input quadrant has to be valid.\n");
    return -1;
  }
  if (is_valid (ancestor_quadrant)) {
    return 0;
  }
  else {
    printf ("ancestor: the output quadrant has to be valid.\n");
    return -1;
  }
}

int
is_ancestor (const quadrant_t * q, const quadrant_t * r)
{
  qcoord_t            mask;

  if (is_valid (q) && is_valid (r)) {
    mask = ~(QUADRANT_LEN (q->level) - 1);
    return (q->level <= r->level) && !((q->x ^ r->x) & mask)
      && !((q->y ^ r->y) & mask)
      && !((q->z ^ r->z) & mask);
  }
  else {
    printf ("is_ancestor: the input quadrants have to be valid.\n");
    return -1;
  }
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
