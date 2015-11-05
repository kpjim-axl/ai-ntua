#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 40

int main(void){
    int i, j;
    int x, y;
    int u;
    int rob1_x, rob1_y;
    int rob2_x, rob2_y;
    srand(time(NULL));
    x = rand()%MAX_SIZE+10;
    y = rand()%MAX_SIZE+10;
    
    fprintf(stderr, "Παρακαλώ, εισάγετε ένα ποσοστό κάλυψης με εμπόδια (μεταξύ 1 και %d):\n", MAX_SIZE * MAX_SIZE);
    scanf("%d",&u);
    fprintf(stderr, "Θα περίπου το 1/%d του πίνακα.\n", u);
    
    printf("%d %d\n", x, y);
    
    rob1_x = rand()%x;
    rob2_x = rand()%x;
    
    rob1_y = rand()%y;
    rob2_y = rand()%y;
    
    printf("%d %d\n", rob2_x+1, rob2_y+1);
    printf("%d %d\n", rob1_x+1, rob1_y+1);
    
    char **bla;
    bla = malloc(x * sizeof( char * ));
    for (i=0; i<x; i++){
	bla[i] = malloc(y * sizeof(char) );
	for (j=0; j<y; j++)
	    bla[i][j] = 'O';
    }
    for (i=0; i<x*y/u; i++){
	int X = rand()%x;
	int Y = rand()%y;
	bla[X][Y] = 'X';
    }
//     printf("bla\n");
    
    bla[rob1_x][rob1_y] = 'O';
    bla[rob2_x][rob2_y] = 'O';
    
    for (i=0; i<y; i++){
	for (j=0; j<x; j++)
	    printf("%c", bla[j][i]);
	printf("\n");
    }
    return 0;
}