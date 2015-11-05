/* File: route.h
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#ifndef ROUTE_H_
#define ROUTE_H_

struct _route{
    int x;
    int y;
    struct _route *next;
};

typedef struct _route route_node;


void route_insert(route_node **, int, int);
void route_insert_end(route_node **, route_node *);

#endif