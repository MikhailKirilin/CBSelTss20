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

/** Test if a quadrant has valid Morton indices.
 * \param [in] q Quadrant to be tested.
 * \return Returns true if \a q is valid.
 */
int                 is_valid (const quadrant_t * q);

/** Compute the position of this child within its siblings.
 * \return Returns its child id in 0..d
 */
int                 child_id (const quadrant_t * q);

/** Compute a specific child of a quadrant.
 * \param [in]     q    Input quadrant.
 * \param [in,out] child_quadrant
 *                      Existing quadrant whose Morton index will be filled
 *                      with the coordinates of its child no. \b child_id.
 * \param [in] child_id The id of the child computed, 0..d.
 */
void                child (const quadrant_t * q, quadrant_t * child_quadrant,
                           int child_id);

/** Compute the parent of a quadrant.
 * \param [in]  q Input quadrant.
 * \param [in,out] parent_quadrant
 *                   Existing quadrant whose Morton index will be filled
 *                   with the Morton index of the parent of \a q.
 * \note \a q may point to the same quadrant as \a parent_quadrant.
 */
void                parent (const quadrant_t * q,
                            quadrant_t * parent_quadrant);

/** Write in the quadrant \a q the coordinates of the root quadrants.
 * \param [out]  q      Quadrant that coordinates will be set to coordinates.
 */
void                root (quadrant_t * q);

/** Compute a specific sibling of a quadrant.
 * \param [in]     q  Input quadrant.
 * \param [in,out] sibling_quadrant
 *                    Existing quadrant whose Morton index will be filled
 *                    with the coordinates of sibling no. sibling_id of q.
 * \param [in]     sibling_id The id of the sibling computed, 0..d.
 */
void                sibling (const quadrant_t * q,
                             quadrant_t * sibling_quadrant, int sibling_id);

/** Compute the ancestor of a quadrant at a given level.
 * \param [in]  q       Input quadrant.
 * \param [in]  level   A smaller or equal level than q.
 * \param [in,out]  ancestor_quadrant
 *                      Existing quadrant whose Morton index will be filled
 *                      with the ancestor of q at the given level.
 * \note The quadrant q may point to the same quadrant as ancestor_quadrant.
 */
void                ancestor (const quadrant_t * q, int level,
                              quadrant_t * ancestor_quadrant);

/** Test if a quadrant is an ancestor of another quadrant.
 * \param [in] q Quadrant to be tested.
 * \param [in] r Descendent quadrant.
 * \return true if \a q is an ancestor of \a r (might be equal).
 */
int                 is_ancestor (const quadrant_t * q, const quadrant_t * r);

/** Compute the first descendant of a quadrant on a given level.
 * \param [in]  q      Input quadrant.
 * \param [out] first_descendant
 *                     First descendant of \a q on level \a level.
 * \param [in]  level  Level must be greater equal than q's level.
 */
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
