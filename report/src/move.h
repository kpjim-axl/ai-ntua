/* File: move.h
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#ifndef MOVE_H_
#define MOVE_H_
#include "heuristics.h"
#include "route.h"
#include "main.h"

struct _node{
    int x;
    int y;			// coordinates
    int h_index;		// heap_index
    int g_score;		// distance from start
    int f_score;		// estimated distance left
    struct _node *sibling;	// for getChildren()
    struct _node *came_from;	// parent
};

typedef struct _node node;

route_node *move_robot1(map_node ***, int (*heuristics)(int, int, int, int));
route_node *move_robot2(map_node ***);

#endif
