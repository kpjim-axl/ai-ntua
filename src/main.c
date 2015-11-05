/* File: main.c
 * Encoding: utf-8
 * Purpose: AI class - A* search algorithm implementation
 * Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>
 */

#include "main.h"
void init_map(map_node *);

int main(int argc, char **argv){
//     map_node **input = getInput(argc, argv);

    if (argc != 2){
	fprintf(stderr, "Usage: ./project input_file\n");
	exit(1);
    }
    
    times = 1;
    // getInput
    FILE *inp_file;
    
    
    map_node ***input;
    int i,j;
    char a;
    
    inp_file = fopen(argv[1], "r");
    
    fscanf(inp_file, "%d %d", &X, &Y);
    fscanf(inp_file, "%d %d", &robot_1_x, &robot_1_y);
    fscanf(inp_file, "%d %d", &robot_2_x, &robot_2_y);
    
    robot_1_x--; robot_1_y--;
    robot_2_x--; robot_2_y--;
        
    input = malloc(X * sizeof( *input ));
    for (i=0; i<X; i++)
	input[i] = malloc(Y * sizeof( **input ));
    
    j=-1; i=X;
    
    do{
	if (i==X){	//new line
	    j++;
	    i=0;
	}
	
	a = (char) fgetc(inp_file);

	if (a=='X'){
	    input[i][j] = malloc(sizeof( ***input ) );
	    input[i][j]->barrier = TRUE;
	    input[i][j]->out = 1;
	    init_map(input[i][j]);
	    i++;
	}
	if (a=='O'){
	    input[i][j] = malloc(sizeof( ***input ) );
	    input[i][j]->barrier = FALSE;
	    input[i][j]->out = 0;
	    init_map(input[i][j]);
	    i++;
	}
	
    }while (a != EOF);
    
    input[robot_1_x][robot_1_y]->out = 2;
    input[robot_2_x][robot_2_y]->out = 3;
    /* Για admissible heuristic function χρησιμοποιούμε την απόσταση manhattan (|x1 - x2| + |y1 - y2|)
     * και για non-admissible heuristic function χρησιμοποιούμε Ευκλείδεια απόσταση (υψομένη στο τετράγωνο)
     * ((x1-x2)^2 + (y1-y2)^2)
     */
    printf("Ok! Input file parsed correctly!\nFor admissible heuristic function press 1 <enter>\nFor non-admissible heuristic function press 2 <enter>\n");
    int heur;
    scanf("%d",&heur);
    if ((heur != 1) && ( heur!=2))
	exit(1);
    
    route_node *temp, *t1;
    
    /* Όσο τα 2 ρομπότ έχουν διαφορετική θέση, το robot_2 θα κινήται (ψευδο)τυχαία στο χώρο
     * και το robot_1 θα το κυνηγάει. Σε κάθε κίνηση αυξάνουμε το times κατα ένα, γιατί το
     * χρειάζεται η συνάρτηση move_robot1(), για να βλέπει να κάποια δομή είναι up to date. Έτσι
     * στο τέλος θα ξέρουμε και πόσες κινήσεις έπρεπε να γίνουν, ώστε το robot_1 να συναντήσει
     * το robot_2
     */
    while ((robot_1_x != robot_2_x) || (robot_1_y != robot_2_y)){
	/* ROBOT_2's turn */
	printf("\e[1;31mROBOT 2:\e[0m ");
	for (i=0; i<SPEED_2; i++){
	    temp = move_robot2(input);
	    robot_2_x = temp->x;
	    robot_2_y = temp->y;
	    
	    printf("(%d, %d) ", robot_2_x + 1, robot_2_y + 1);
	    input[temp->x][temp->y]->out = 3;
	    
	    free(temp);
	}
	

	/* ROBOT_1's turn */
	printf("   \e[1;34mROBOT 1:\e[0m ");
	if (heur == 1)
	    temp = move_robot1(input, manhattan);
	else
	    temp = move_robot1(input, squaredDist);
	for (i=0; i<SPEED_1; i++){
	    t1 = temp;
	    printf("(%d, %d) ", temp->x + 1, temp->y + 1);
	    input[temp->x][temp->y]->out = 2;
	    if (temp->next == NULL)
		break;
	    else
	    {
		temp = temp->next;
		free(t1);
	    }
	}
	robot_1_x = temp->x;
	robot_1_y = temp->y;
	while (temp->next){
	    t1 = temp;
	    temp = temp->next;
	    free(t1);
	}
	printf("\n");
	times++;
    }
    
    printf("\n \e[1m0\e[0m  ");
    for (i=0; i<X; i++)
	if ((i+1)%10)
	    printf("%d ",(i+1)%10);
	else
	    printf("\e[1m0\e[0m ");
    printf("\n");
    char c = 'B';
    for (i=0; i<Y; i++){
	if (!((i+1)%10) && i>1)
	    printf(" \e[1m%d\e[0m  ", 0);
	else
	    printf(" %d  ",((i+1)%10));
	    
	for (j=0; j<X; j++){
	    switch (input[j][i]->out){
		case 0:		// Not a barrier, not a robot
		    printf("\e[4;47m%c\e[0m|", c);
		    break;
		case 1:		// Barrier
		    printf("\e[4;1;30;40m%c\e[0m|", c);
		    break;
		case 2:		// Robot 1
		    printf("\e[4;44m1\e[0m|");
		    break;
		case 3:		// Robot 2
		    printf("\e[4;41m2\e[0m|");
		    break;
	    }
	}
	printf("\n");
    }
    
    printf("\e[1;44mROBOT_1:\e[0m It took me %d moves to reach my enemy\n", times-1);
    
    return 0;
}

void init_map(map_node *bla){
    bla->opened = 0;
    bla->closed = 0;
    bla->search_node = NULL;
}