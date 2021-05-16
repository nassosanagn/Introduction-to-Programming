#include <stdio.h>
#include <stdlib.h>

#define INF -1

void solve(int n ,int **graph);

int flowarrec(int i,int j,int k,int **graph);
int flowarmem(int i,int j,int k,int **graph,int ***A);
