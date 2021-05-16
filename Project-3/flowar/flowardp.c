/* File: flowardp.c */

#include "myheaderfile.h"

void solve(int n ,int **graph){

int i,j,k,**Q;

#ifdef PATH			/* ���������� ��� ������ P ��� ��� ���������� ��� ��������� ���������� ��� ���� ������� � ������� PATH */

int **P,u;

	P = malloc(n * sizeof(int*));

	if(P == NULL){
		printf("Sorry, cannot allocate memory \n");
		return;
	}

	for(i=0;i<n;i++){
		P[i] = malloc(n * sizeof(int));

		if(P[i] == NULL){
			printf("Sorry, cannot allocate memory \n");
			return;
		}
	}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			P[i][j] = j;

#endif

	Q = malloc(n * sizeof(int *));		/* ���������� ��� ������ Q ��� ��� ���������� ��� ��������� ������� */

		if(Q == NULL){
			printf("Sorry, cannot allocate memory \n");
			return;
		}

	for(i=0;i<n;i++){
		Q[i] = malloc(n * sizeof(int));

		if(Q[i] == NULL){
			printf("Sorry, cannot allocate memory \n");
			return;
		}
	}

	for(i=0;i<n;i++)		/* �� �������� ��� ������ graph ������������� ���� ������ Q */
		for(j=0;j<n;j++)	
			if(i == j)
				Q[i][j]=0;
			else if(j < i)
				Q[i][j] = graph[i][j];
			else
				Q[i][j] = graph[j][i];


	for(k=0;k<n;k++)					/* ����������� ��� ��������� ������� ��� ��� ��������� ����������, �� ���� ������� � ������� PATH */
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if((Q[i][k] == INF) ||(Q[k][j] == INF))
					Q[i][j] = Q[i][j];
				else
					 if((Q[i][j] > Q[i][k] + Q[k][j]) || (Q[i][j] == INF)){
						Q[i][j] = Q[i][k] + Q[k][j];
						#ifdef PATH
							P[i][j] = P[i][k];
						#endif
					}

		for(i=0;i<n;i++){			/* �������� ��� ��������� ������� ������ ��� ������ ��� ������ ��� �������� ��� ��������� ����������, �� ���� ������� � ������� PATH */
			for(j=0;j<i;j++){
				if(Q[i][j] == INF)
					printf("From node %3d to node %3d: There is no path \n",i,j);
				else{
					printf("From node %3d to node %3d: Length of shortest path is %d \n",i,j,Q[i][j]);

					#ifdef PATH
					printf("\tShortest path is: %3d",i);
					u=i;

					while(u!=j){
						printf(" -> %3d",P[u][j]);
						u = P[u][j]; }
					printf("\n");
					#endif
				}
			}
		printf("\n");
		}


	for(i=0;i<n;i++)			/* ����������� ��� ������ Q*/
		free(Q[i]);
	free(Q);

	#ifdef PATH
	for(i=0;i<n;i++)			/* ����������� ��� ������ P, �� ���� ������� � ������� PATH*/
		free(P[i]);
	free(P);
	#endif

}
