/* File: route.c
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#include "route.h"
#include <stdlib.h>
#include <stdio.h>

/* Η route_insert_end() εισάγει τα νέα στοιχεία στη λίστα,
 * με δεδομένο πως το *r είναι pointer στο πρώτο στοιχείο της
 * λίστας αυτής.
 */
void route_insert(route_node **r, int x, int y){
    route_node *temp;
    temp = malloc(sizeof(route_node));
    temp->x = x;
    temp->y = y;
    temp->next = *r;
    *r = temp;
}


/* Η route_insert_end() εισάγει τα νέα στοιχεία στη λίστα,
 * με δεδομένο πως το *r είναι pointer στο τελευταίο στοιχείο της
 * λίστας αυτής. (το *r ανανεώνεται) 
 * edit: Τελικά δε χρειάστηκε κάπου..
 */
void route_insert_end(route_node **end, route_node *new){
    /* make the last element of the list pointing *new */
    if ((*end) == NULL)
	*end = new;
    else
	(*end)->next = new;
    
    /* make (*e) pointing the last element of the list */
//     if ((*end) != NULL)
// 	while ((*end)->next != NULL)
// 	    *end = (*end)->next;
}
