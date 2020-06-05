/** \file tree_based_quadrants.h
 *
 * Some basic functions for ocants.
 *
 */

#ifndef TREE_BASED_QUADRANTS_H
#define TREE_BASED_QUADRANTS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAXLEVEL 19

/** The length of a quadrant of level l */
#define QUADRANT_LEN(l) ((int) 1 << (MAXLEVEL - (l)))

/** Typedef for quadrant coordinates. */
typedef int32_t     qcoord_t;

/** The 3D quadrant (octant) datatype */
typedef struct quadrant
{
  qcoord_t            x, y, z;
                     /**< coordinates */
  int8_t              level;
                    /**< level of refinement */
}
quadrant_t;

int                 is_valid (const quadrant_t * q);

int                 child_id (const quadrant_t * q);

void                child (const quadrant_t * q, quadrant_t * child_quadrant,
                           int child_id);

/** Write in the quadrant \a q the coordinates of the root quadrants.
 * \param [out]  q      Quadrant that coordinates will be set to coordinates.
 */
void                root (quadrant_t * q);

void                sibling (const quadrant_t * q,
                             quadrant_t * sibling_quadrant, int sibling_id);

void                ancestor (const quadrant_t * q, int level,
                              quadrant_t * ancestor_quadrant);

int                 is_ancestor (const quadrant_t * q, quadrant_t * r);

void                first_descendant (const quadrant_t * q,
                                      quadrant_t * first_descendant,
                                      int level);

/** Compute the last descendant of a quadrant on a given level.
 * \param [in]  q      Input quadrant.
 * \param [out] ld     Last descendant of \a q on level \a level.
 * \param [in]  level  Level must be greater equal than q's level.
 */
void                last_descendant (const quadrant_t * q,
                                     quadrant_t * last_descendant, int level);

#endif /* !TREE_BASED_QUADRANTS_H */
