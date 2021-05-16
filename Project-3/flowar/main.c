/*File: main.c */

#include "myheaderfile.h"

int main(){
	
int **graph,N,i,j;			/* Πρώτα διαβάζεται το Ν που είναι το πλήθος των κόμβων του γράφου */
	
	scanf("%d",&N);
		
	graph = malloc(N * sizeof(int *));	
	
	if(graph == NULL){
		printf("Sorry, cannot allocate memory \n"); 
		return -1;
	 }
		
	for(i=0;i<N;i++){
		
		graph[i] = malloc(i * sizeof(int));			/* Κάθε γραμμή θα έχει i στοιχεία επειδή ο πίνακας είναι τριγωνικός */
			
		if(graph[i] == NULL){
			printf("Sorry, cannot allocate memory \n"); 
			return -1;
		}
	}	
			
			
	for(i=0;i<N;i++)		/* Στον πίνακα καταχωρούνται τα στοιχεία του γράφου που διαβάζονται απο την είσοδο */
		for(j=0;j<i;j++)
			scanf("%d,",&graph[i][j]);
					
	
	solve(N,graph);
			

	for(i=0;i<N;i++)			/* Αποδέσμευση του πίνακα graph*/
		free(graph[i]);
	free(graph);	
	
}






	
	
	
	


