/* File: flowarmem.c */

#include "myheaderfile.h"

void solve(int n ,int **graph){
	
int i,j,k,result,***A;
	
	A = malloc(n * sizeof(int **));
	
	if(A == NULL){
		printf("Sorry, cannot allocate memory \n");			/* Αν η malloc επιστρέψει NULL τότε η solve επιστρέφει το κενό στη main και το πρόγραμμα τερματίζει */  
		return;
    }
	
	for(i=0;i<n;i++){
		
		A[i] = malloc(n * sizeof(int *));
		
		if(A[i] == NULL){
			printf("Sorry, cannot allocate memory \n"); 
			return;
		}

		for(j=0;j<n;j++){	
		
			A[i][j] = malloc((n+1) * sizeof(int));
			
			if(A[i][j] == NULL){
				printf("Sorry, cannot allocate memory \n"); 
				return;
			}
		}
	}
	
	
	for(i=0;i<n;i++)			/* Αρχικοποιώ τον πίνακα σε έναν αρνητικό αριθμό, ο οποίος δεν υπάρχει περίπτωση να προκύψει στην συνέχεια μέσω των υπολογισμών */
		for(j=0;j<n;j++)
			for(k=0;k<n+1;k++)
				A[i][j][k] = -5;
				

	for(i=1;i<n;i++){			/* Εμφάνιση του ελάχιστου κόστους μεταξύ των κόμβων του γράφου */
		for(j=0;j<i;j++){
				result = flowarmem(i,j,n-1,graph,A);
				if(result != INF)
					printf("From node %3d to node %3d: Length of shortest path is %d \n",i,j,result);
				else
					printf("From node %3d to node %3d: There is no path \n",i,j);
			}		
		printf("\n");
	}
	
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)	
			free(A[i][j]);

		free(A[i]);
	}
	free(A);
}


int flowarmem(int i,int j,int k,int **graph ,int ***A){
	
int a,b,c,temp,sum;

	
	if(j>i){			/* Γιατί απο τον γράφο i στον γράφο j είναι το ίδιο απο τον γράαφο j στο i ,οπότε αντιμεταθέτω τα i,j ώστε να μην βγω εκτος των ορίων του πίνακα */
		temp=i;
		i=j;
		j=temp;	
	}
	
	if(i==j){
		A[i][j][k+1] = 0;
		return 0;
	}
		
	if(k>=0){
			
		if(A[i][j][k] == -5)			/* Οπότε υπάρχει -5 στον πίνακα σημαίνει πως δεν έχει πάρει ακόμα τιμή,και πρέπει να υπολογιστεί αλλιώς η τιμή έχει ήδη υπολογιστεί είναι έτοιμη*/
			a = flowarmem(i,j,k-1,graph,A);
		else
			a = A[i][j][k];
		
		if(A[i][k][k] == -5)	
			b = flowarmem(i,k,k-1,graph,A);
		else
			b = A[i][k][k];
		
		if(A[k][j][k] == -5)		
			c = flowarmem(k,j,k-1,graph,A); 
		else
			c = A[k][j][k];	
			
		if((b == INF)||(c == INF)){	
			A[i][j][k+1] = a;
			return a; 
		}
				
		sum = b+c;
		
		if(a == INF){
			A[i][j][k+1] = sum;
			return sum;
		}
			
		if(a < sum){
			A[i][j][k+1] = a;
			return a;	
		}else{
			A[i][j][k+1] = sum;
			return sum;	
		}	
	
	}else{
		
		A[i][j][k+1] = graph[i][j];
		return graph[i][j]; 	}
	
}






	
	
	
	


