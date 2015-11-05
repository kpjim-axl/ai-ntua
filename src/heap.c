/* File: heap.c
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
void swap( heap_node *, heap_node *, int, int);

void init_heap(struct hcb **heap, int length){
    (*heap) = malloc( sizeof( **heap ) );
    (*heap)->heap_array = malloc( length * sizeof( heap_node ) );
    (*heap)->length = length;
    (*heap)->last = -1;
}

void destroy_heap(struct hcb *heap){
    free(heap->heap_array);
    free(heap);
}

/* insert (at the end of the heap) new data and then
 * reorganize the heap */
void insert_h(struct hcb *heap, node *a) {
    int index = ++(heap->last);
    
//     heap->heap_array[index].cost= a->f_score;
    heap->heap_array[index].data = a;
    
    a->h_index = index;
    
    update_h(heap, index);
}

/* update the heap, because heap[index] is placed in
 * a wrong position */
void update_h(struct hcb *heap, int index){
    int parent = (index-1) / 2;
    
    heap->heap_array[ index ].cost = heap->heap_array[ index ].data->f_score;
    
    while ( heap->heap_array[ index ].cost < heap->heap_array[ parent ].cost ){
	/* swap elements */
	
	
// 	(heap->heap_array[index].data)->h_index = parent;
// 	(heap->heap_array[parent].data)->h_index = index;
	swap( heap->heap_array + index, heap->heap_array + parent, index, parent);
	
	index = parent;
	parent = (index-1) / 2;
    }
}

void swap( heap_node *a, heap_node *b , int index_a, int index_b){
    heap_node temp;
    
    a->data->h_index = index_b;
    b->data->h_index = index_a;
    
    temp = *a;
    *a = *b;
    *b = temp;

}

void combine(struct hcb *heap, int index){
    int l_child = 2*index + 1;
    int r_child = 2*index + 2;
    int mp = index;
    
    if ((l_child <= heap->last) && ( heap->heap_array[ l_child ].cost < heap->heap_array[ mp ].cost ))
	mp = l_child;
    if ((r_child <= heap->last) && ( heap->heap_array[ r_child ].cost < heap->heap_array[ mp ].cost ))
	mp = r_child;
    if (mp != index){
	/* swap elements */
	
// 	(heap->heap_array[index].data)->h_index = mp;
// 	(heap->heap_array[mp].data)->h_index = index;
	swap( heap->heap_array + index, heap->heap_array + mp, index, mp);
	
	/* combine from mp */
	combine(heap, mp);
    }
}

node *return_min( struct hcb *heap ){
    
//     heap_node *ret = malloc (sizeof (heap_node));
//     *ret = heap->heap_array[0];
    
    node *ret = heap->heap_array[0].data;
//     heap_node ret = heap->heap_array[0];
    
    heap->heap_array[0] = heap->heap_array[ heap->last ];
    heap->last -= 1;
    combine(heap, 0);
    return ret;
}

int empty( struct hcb *heap ){
    return (heap->last == -1);
}

// test heap using heapsort and qsort comparison
int comp(const void *, const void *);

int comp(const void *a, const void *b){
    if ( *(const int *)a < *(const int *)b)
	return -1;
    if (*(const int *)a == *(const int *)b)
	return 0;
    else
	return 1;
}

/*

int main(void){
    int n;
    struct hcb *h;
    node *input;
    int i;
    scanf("%d",&n);
    
    int *h_sort;
    int *q;
    h_sort = malloc(n*sizeof(int));
    q = malloc(n*sizeof(int));
    
    
    init_heap(&h, n);
    
    input = malloc(n*sizeof(node));
    
    for (i=0; i<n; i++){
	int m;
	scanf("%d",&m);
	input[i].f_score = m;
	insert_h(h, input+i);
	if (i%2){
	    input[i].f_score--;
	    update_h(h, input[i].h_index);
	}
    }
    
    for (i=0; i<n; i++){
	node *a;
	a = return_min(h);
	h_sort[i] = a->f_score;
	
	q[i] = h_sort[i];
    }
    
    qsort(q, n, sizeof(int), comp);
    
    for (i=0;i<n;i++){
	if (h_sort[i] != q[i]){
	    printf("error\n");
	    exit(1);
	}
    }
    
    destroy_heap(h);
    printf("all done\n");
    
    return 0;
}


*/