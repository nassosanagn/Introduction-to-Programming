/*File: main.c */

#include "myheaderfile.h"

int main(){
	
int **graph,N,i,j;			/* ����� ���������� �� � ��� ����� �� ������ ��� ������ ��� ������ */
	
	scanf("%d",&N);
		
	graph = malloc(N * sizeof(int *));	
	
	if(graph == NULL){
		printf("Sorry, cannot allocate memory \n"); 
		return -1;
	 }
		
	for(i=0;i<N;i++){
		
		graph[i] = malloc(i * sizeof(int));			/* ���� ������ �� ���� i �������� ������ � ������� ����� ���������� */
			
		if(graph[i] == NULL){
			printf("Sorry, cannot allocate memory \n"); 
			return -1;
		}
	}	
			
			
	for(i=0;i<N;i++)		/* ���� ������ ������������� �� �������� ��� ������ ��� ����������� ��� ��� ������ */
		for(j=0;j<i;j++)
			scanf("%d,",&graph[i][j]);
					
	
	solve(N,graph);
			

	for(i=0;i<N;i++)			/* ����������� ��� ������ graph*/
		free(graph[i]);
	free(graph);	
	
}






	
	
	
	


