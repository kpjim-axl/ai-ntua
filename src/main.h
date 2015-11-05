/* File: main.h
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include "route.h"

#define TRUE 1
#define FALSE 0

#define SPEED_1 3
#define SPEED_2 1

typedef struct __map_node{
    int opened;		// if (opened == times), search_node is valid and open
    int closed;		// if (closed == times), search_node is valid and closed
    int barrier;	// TRUE if 'X', FALSE if 'O'
    int out;
    struct _node *search_node;	// pointer to the search_node of map_node
} map_node;

#include "move.h"

int X, Y;
int robot_1_x, robot_1_y;
int robot_2_x, robot_2_y;
int times;

#endif