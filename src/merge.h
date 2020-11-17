#ifndef MERGE_H
#define MERGE_H

#define MERGE_GOAL (int)((sizeof(merge_values)/sizeof(merge_values[0]))-1)

const long merge_values[] = {
    0, 2, 4, 8, 16, 32, 64, 128, 256, 512,
    1024, 2048
};

/* When defining a new set of rules, remember that the grid values (and the
 * therefore the arguments v1, v2) are index values and should be treated as
 * such */

/* This should return the value of a given index. 0 should default to 0 (empty) */
inline long merge_value(const int v1)
{
    return v1 <= MERGE_GOAL ? merge_values[v1] : -1;
}

/* This should return the goal index value */
inline long merge_goal(void)
{
    return MERGE_GOAL;
}

/* Return if a merge is possible between two indices */
inline int merge_possible(const int v1, const int v2)
{
    return v1 == v2;
}

/* The result of a merge of two values. If the two parameters are not mergeable,
 * then a -1 error code is the suggested return value */
inline int merge_result(const int v1, const int v2)
{
    return merge_possible(v1, v2) ? v1 + 1 : -1;
}

#endif
