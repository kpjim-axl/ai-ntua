/* File: move.c
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "move.h"
#include "main.h"
#include "heap.h"

route_node *reconstruct_path(node *);

node *makeChildren(int , int, map_node ***);
node *getChildren(node *, map_node ***);

/* Με τη makeChildren() ελέγχουμε αν στη θέση του χώρου (x, y) υπάρχει εμπόδιο.
 * Αν υπάρχει επιστρέφει NULL, διαφορετικά:
 * * αν υπάρχει search_node για τη θέση αυτή, επιστρέφει ένα δείκτη σε αυτό
 * * αν δεν υπάρχει search_node το δημιουργεί και επιστρέφει ένα δείκτη σε αυτό
 */
node *makeChildren(int x, int y, map_node ***map){
    node *ret;
    if (!map[x][y]->barrier){
	
	if ( map[x][y]->search_node != NULL ){
	    ret = map[x][y]->search_node;
	}
	else{
	    map[x][y]->search_node = malloc( sizeof(node) );
	    ret = map[x][y]->search_node;
	    ret->x = x;
	    ret->y = y;
	}
    }
    else
	ret = NULL;
    return ret;
}

/* Με τη getChildren() βρίσκουμε όλους τους γείτονες μιας συγγεκριμένης θέσης.
 * Επιστρέφει ένα δείκτη που δείχνει στον πρώτο από αυτούς τους γείτονες (αφού
 * τους κάνει να δείχνουν ο ένας τον άλλο, σαν αδελφό).
 */
node *getChildren(node *currentNode, map_node ***map){
    int x, y;
    int i;
    node *ret = NULL;
    node *temp = NULL;
    node *bla[4];
    x = currentNode->x;
    y = currentNode->y;
    
    if ((x+1)==X)
	bla[0] = NULL;
    else
	bla[0] = makeChildren(x+1, y, map);
    
    if ((x-1)<0)
	bla[1] = NULL;
    else
	bla[1] = makeChildren(x-1, y, map);
    
    if ((y+1)==Y)
	bla[2] = NULL;
    else
	bla[2] = makeChildren(x, y+1, map);
    
    if ((y-1)<0)
	bla[3] = NULL;
    else
	bla[3] = makeChildren(x, y-1, map);
    
    /* ret points to the first child */
    for (i=3; i>=0; i--)
	if (bla[i] != NULL)
	    ret = bla[i];
    temp = ret;
    /* its child points to a sibling */
    for (; i<4; i++)
	if (bla[i] != NULL){
	    temp->sibling = bla[i];
	    temp = temp->sibling;
	}
    temp->sibling = NULL;

    return ret;
}

/* Υλοποίηση του αλγορίθμου Α*. Τον χρησιμοποιεί το robot_1 */
route_node *move_robot1(map_node ***map, int (*heuristics)(int, int, int, int)){
    struct hcb *open;
    
    /* open queue initialize */
    init_heap(&open, X*Y);
    node *start;
    
    if ( map[ robot_1_x ][ robot_1_y ]->search_node == NULL){
	map[ robot_1_x ][ robot_1_y ]->search_node = malloc( sizeof(node) );
    }
    
    start = map[ robot_1_x ][ robot_1_y ]->search_node;
    start->x = robot_1_x;
    start->y = robot_1_y;
    start->g_score = 0;
    start->f_score = heuristics( robot_1_x, robot_2_x, robot_1_y, robot_2_y );
    start->came_from = NULL;
    
    node *current;
    insert_h(open, start);
    
    while (!empty(open)){
	current = return_min( open );
	if ( (current->x == robot_2_x) && (current->y == robot_2_y) ){		// if current == goal
	    route_node *r = reconstruct_path(current);
	    destroy_heap(open);
	    return r;
	}
	
	map[ current->x ][ current->y ]->closed = times;		// add current to closed set
	
	node *child = getChildren( current , map);			// define getChildren()
	
	while (child != NULL){
	    int tent_g_score = current->g_score + 1;

	    if ( map[ child->x ][ child->y ]->closed == times )		// if neighbor in closed set ( ==> child->search_node is up to date )
		if (tent_g_score >= child->g_score){
		    child = child->sibling;
		    continue;
		}
	    
	    if ( ( map[ child->x ][ child->y ]->opened != times ) || ( tent_g_score < child->g_score ) ){
		child->came_from = current;
		child->g_score = tent_g_score;
		child->f_score = tent_g_score + heuristics(child->x, robot_2_x, child->y, robot_2_y);		// heur between child and goal!!
		
		if ( map[ child->x ][ child->y ]->opened != times ){
		    insert_h(open, child);
		    map[ child->x ][ child->y]->opened = times;
		}
		else
		    update_h(open, child->h_index);
	    }
	    /* proceed to the next neighbor */
	    child = child->sibling;
	}
    }
    
    /* astar failed */
    printf("Can't reach my enemy.. 'night!\n");
    destroy_heap(open);
    exit(0);
}

route_node *reconstruct_path(node *current){
    node *temp = current;
    route_node *r = NULL;
    while (temp){
	route_insert(&r, temp->x, temp->y);
	temp = temp->came_from;
    }
    return r;
}

route_node *move_robot2(map_node ***map){
    node *bla[4];
    node *temp = NULL;
    route_node *ret;
    int i;
    int x = robot_2_x;
    int y = robot_2_y;
    
    
    if ((x+1)>=X)
	bla[0] = NULL;
    else
	bla[0] = makeChildren(x+1, y, map);
    
    if ((x-1)<0)
	bla[1] = NULL;
    else
	bla[1] = makeChildren(x-1, y, map);
    
    if ((y+1)>=Y)
	bla[2] = NULL;
    else
	bla[2] = makeChildren(x, y+1, map);
    
    if ((y-1)<0)
	bla[3] = NULL;
    else
	bla[3] = makeChildren(x, y-1, map);
//     sleep(1);
    srand(time(NULL));    
    i = rand();
    while (temp == NULL){
	i = (i+1);
	i = i%4;
	temp = bla[i];
    }
    ret = malloc(sizeof(route_node));
    ret->x = temp->x;
    ret->y = temp->y;
    ret->next = NULL;
    return ret;
}

    
/*	TO_DO
 * define getChildren()
 * define reconstruct_path()
 * debug..:/
 * extra caution in on_date nodes (if a node is not up to date, built scores again)
 * give 'next' for recursive reconstruct_path()
 */
