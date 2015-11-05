/* File: heap.h
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#ifndef HEAP_H_
#define HEAP_H_

#include "move.h"	// defines struct node {}
#include "main.h"

typedef struct _heap_node{
    int cost;
    node *data;
} heap_node;

struct hcb{
    heap_node *heap_array;
    int length;
    int last;
};

void init_heap(struct hcb **, int);
void destroy_heap(struct hcb *);
void insert_h(struct hcb *, node *);
void update_h(struct hcb *, int);
int empty(struct hcb *);
node *return_min(struct hcb *);

#endif
