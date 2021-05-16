/*File: flowarrec.c */

#include "myheaderfile.h"

void solve(int n ,int **graph){
	
int i,j,result;
	
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
				result = flowarrec(i,j,n-1,graph);
				if(result != INF)
					printf("From node %3d to node %3d: Length of shortest path is %d \n",i,j,result);
				else
					printf("From node %3d to node %3d: There is no path \n",i,j);
		}
		printf("\n");
	}
}


int flowarrec(int i,int j,int k,int **graph ){
	
int a,b,c,temp,sum;


	if(j>i){			/* Γιατί απο τον γράφο i στον γράφο j είναι το ίδιο απο τον γράαφο j στο i ,οπότε αντιμεταθέτω τα i,j ώστε να μην βγω εκτος των ορίων του πίνακα */
		temp=i;
		i=j;
		j=temp; }	
	
	if(i==j)
		return 0;
		
	if(k>=0){
				
		a = flowarrec(i,j,k-1,graph);
		b = flowarrec(i,k,k-1,graph);
		c = flowarrec(k,j,k-1,graph); 
		
		if((b == INF)||(c == INF))
			return a;
			 	
		sum = b+c;
			 	
		if(a == INF)
			return sum;
		
		if(a < sum)
			return a;
		else
			return sum;				
	
	}else									
		return graph[i][j];		/* Αν η τιμη του graph[i][j] είναι -1 θα επιστραφεί το -1 όπου δεν θα υπάρχει απευθείας σύνδεση μεταξύ των κόμβων αλλιώς θα επιστραφεί η απόσταση τους */		

}

