
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct listnode *Listptr;

void insert_at_start(Listptr *ptraddr,int number,int letter);			/* � ��������� ��������� ��� ������� ������ ���� ���� ��� ������ */

void delete_first_node(Listptr *ptraddr,char **A);						/* � ��������� ��������� ��� ����� ����� ��� ��� ������� ������ ��� ��� ������ �.�. �� ��������� undo */

int mikos(int i,int j,const char ch,int size,bool flagw,bool flagb,char **A);	/* � ��������� ���������� �� ����� ��� ��� ���������� ��������� ��� ������������ ������������ �������� */

int utility(int *maxw,int *maxb,int size,char **A);		/* � ��������� ������� �� ���������� ��������� ��� ���������� �������� ��� ���� ������ ��� ������ ������� �� �������� �� ��������*/


struct listnode{					/* � ����� ���������� ��� �������� ��� ����� ������� */
	int number;
	int letter;
	Listptr next;
};
