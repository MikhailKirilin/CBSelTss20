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

/** The finest level of the quadtree for representing quadrants */
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

int                 is_equal (const quadrant_t * q, const quadrant_t * r);

/** Compute the position of this child within its siblings.
 * \return Returns its child id in 0..d
 */
int                 child_id (const quadrant_t * q);

/** Compute a specific child of a quadrant.
 * \param [in]     q    Input quadrant.
 * \param [in,out] child_quadrant
 *                 Existing quadrant whose Morton index will be filled
 *                 with the coordinates of its child no. \b child_id.
 * \param [in]     child_id The id of the child computed, 0..d.
 */
int                 child (const quadrant_t * q, quadrant_t * child_quadrant,
                           int child_id);

int                 is_child (const quadrant_t * q, const quadrant_t * r);

/** Compute the parent of a quadrant.
 * \param [in]  q Input quadrant.
 * \param [in,out] parent_quadrant
 *                   Existing quadrant whose Morton index will be filled
 *                   with the Morton index of the parent of \a q.
 * \note \a q may point to the same quadrant as \a parent_quadrant.
 */
int                 parent (const quadrant_t * q,
                            quadrant_t * parent_quadrant);

/** Test if a quadrant is the parent of another quadrant.
 * \param [in]  q Quadrant to be tested.
 * \param [in]  r Child quadrant.
 * \return true if \a q is the parent of \a r.
 */
int                 is_parent (const quadrant_t * q, const quadrant_t * r);

/** Write in the quadrant \a q the coordinates of the root quadrants.
 * \param [out]  q      Quadrant that coordinates will be set to coordinates
 *                      and level of the root quadrant.
 */
void                root (quadrant_t * q);

/** Compute a specific sibling of a quadrant.
 * \param [in]     q  Input quadrant.
 * \param [in,out] sibling_quadrant
 *                    Existing quadrant whose Morton index will be filled
 *                    with the coordinates of sibling no. sibling_id of q.
 * \param [in]     sibling_id The id of the sibling computed, 0..d.
 */
int                 sibling (const quadrant_t * q,
                             quadrant_t * sibling_quadrant, int sibling_id);

int                 is_sibling (const quadrant_t * q, const quadrant_t * r);

/** Compute the ancestor of a quadrant at a given level.
 * \param [in]  q       Input quadrant.
 * \param [in]  level   A smaller or equal level than q.
 * \param [in,out]  ancestor_quadrant
 *                      Existing quadrant whose Morton index will be filled
 *                      with the ancestor of q at the given level.
 * \note The quadrant q may point to the same quadrant as ancestor_quadrant.
 */
int                 ancestor (const quadrant_t * q, int level,
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
int                 first_descendant (const quadrant_t * q,
                                      quadrant_t * first_descendant,
                                      int level);

/** Compute the last descendant of a quadrant on a given level.
 * \param [in]  q      Input quadrant.
 * \param [out] ld     Last descendant of \a q on level \a level.
 * \param [in]  level  Level must be greater equal than q's level.
 * \return             Returns -1 if the given quadrant \a q is not valid
 *                                or level is not in [q->level, MAXLEVEL),            
 *                              0 if all preconditions are satisfied.
 */
int                 last_descendant (const quadrant_t * q,
                                     quadrant_t * ld, int level);

#endif /* !TREE_BASED_QUADRANTS_H */
