/* File: heuristics.c
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#include "heuristics.h"
/* ??? */
int mpow(int a, int b){
	int t = a;
	while (b--)
		a *= t;
	return a;
}
/* Απόσταση Manhattan */
int manhattan(int x1, int y1, int x2, int y2){
    return (abs(x1-x2) + abs(y1-y2));
}

/* Ευκλείδεια απόσταση */
int squaredDist(int x1, int y1, int x2, int y2){
    return ( mpow( (x1-x2), 2) + mpow( (y1-y2), 2 ) );
}
