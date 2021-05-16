
#include "myheader1.h"
#include "myheader2.h"

void showstate(const int size,char **A){
	
	int i,j,middle,spaces = 0;
	char ch = 'A';
	
	for(i=0; i<size ;i++){
		
		if(i == 0){	
		
			for(j=0 ; j < size/2 ; j++)		/* �������� ��� WHITE ���� ���� */
				printf("    ");
			printf("W H I T E \n");
		
		
			printf("    ");	
			for(j=0 ; j < size ; j++)				/* �������� ��� ��������� A,B,C... ���� ���� */
				printf("  %c ",ch++);			
			printf("\n    ");
		
			for(j=0 ; j < size ; j++)
				printf("  _ " );
			printf("\n     ");
				
		
			for(j=0 ; j < size ; j++)
				printf("/ \\_");	
			printf("\n");
			
			spaces += 4;			/* � ������� ��� ����� ��� ��� ���� ���� ������ */
		}
		
		middle = (size/2)-1;				/* � ���� ��� �������� (�������) ���� �� ��������� �� BLACK ��� �� WHITE */
		
		for(j=0 ; j< spaces-4 ; j++)
			printf(" ");		
		
		if(i == middle)
			printf("\b\bB ");
			
		else if(i == middle+1)
			printf("\b\bA ");
		
		else if(i == middle+2)
			printf("\b\bK ");
		
		
		if(i<9)						/* �������� ��� ������� ��� �������� , ������� ������� �� � ������� ���� 1 � 2 ����� ����� ���� ���� 2 �� ���� ��� �������� ���� */
			printf(" %d  ",i+1);
		else
			printf(" %d ",i+1);
					
				
		for(j=0 ; j < size ; j++)
			printf("| %c ",A[i][j]);
		printf("|");		
		printf("  %d",i+1);			/* �������� ��� ������� ��� �����*/
		printf("\n");
		
		for(j=0; j <= spaces ; j++){
			
			if((i == middle)&&(j == spaces-5))
					printf("L");
			else if((i == middle+1)&&(j == spaces-5))
					printf("C");	
			else	
				printf(" ");
		}

	
		for(j=0; j<size ;j++)
			printf("\\_/ ");	
		if(i != size-1)	
			printf("\\");	
		printf("\n");
		
		spaces += 2;		
	}
	
	for(j=0 ; j <= spaces-2 ;j++)		/* �������� ��� ��������� A,B,C... ��� ����� */
		printf(" ");
		
	ch = 'A';						
	for(j=0; j < size ; j++)
		printf(" %c  ",ch++);
	printf("\n");	
}


int play(Listptr *listhead,char buf[],int size,char ch,char **A){
	
	int number,letter;
	int i,j,maxw,maxb;
	char **temp;
	
	if(buf[8] != '\0'){
		fprintf(stderr,"Error: Too many arguments \n");  return -1; }

	
	letter = buf[5] - 'A';		/* � 5�� ��� ����� ���������� ����� � A,B,..*/
	number = atoi(buf+6);		/* � 6�� ��� ����� ���������� ����� � ������� */
	
	if( (buf[5]<'A') || (buf[5]>'A'+size-1) || (number< 1) || (number>size) ){
		fprintf(stderr,"Error: Invalid coordinates \n");  
		return -1; 
	}
		
	if( A[number-1][letter] != ' '){
		fprintf(stderr,"Error: Move already played \n"); return -1;
	}else
		A[number-1][letter] = ch;					/* number -1 ������ �� ������ ��� ������ ����� [0,size-1] ��� ��� [1,size] ���� �������� ��� ����� */		
	
	
	insert_at_start(listhead,number-1,letter);			/* ������������� ����� ��� ���������� ��� �������� ��� ���� ��� ������ ������������� ���� ���� */
	
	printf("Move played: %c%d \n",buf[5],number);
	
	utility(&maxw,&maxb,size,A);		/* � ��������� ��������������� ��� �� ������� ��� ������� ������� ������� */
													
	return number;
}



int swap(Listptr listhead,bool swap_on,int counter,char **A){

	if(listhead->next != NULL){													/* ������ �� swap ����������� ���� ��� ����� ������ */
		fprintf(stderr,"This is not the first move \n"); return -1; }
		
	if(swap_on == false){
		fprintf(stderr,"The swap rule is not active \n"); return -1; }
			
	int temp1,temp2;
			
	temp1 = listhead->number;
	temp2 = listhead->letter;
			
	delete_first_node(&listhead,A);			/* ����������� � 1�� ������ ��� ���� ��� ������ ��� ������ ������ */
			
	insert_at_start(&listhead,temp2,temp1);		/* ��� ������� ������������� �� ��� ���������� ������ ��� ��� ����� ������ */ 
			
	A[temp2][temp1] = 'b';
	
	return 0;
}


void newgame(char buffer[],int *size,bool *b,bool *swap_on){			/* � ��������� ���������� �� �������� ��� ���� ���������� ���� ������� */

	int i;
	char *temp;	
			
	temp = strtok(buffer," ");
			
	for(i=0; temp!= NULL ; i++){
				
				
		if(i==0){
			if(strcmp(temp,"newgame\n") == 0)
				break;
					
		}else if(i == 1){
					
			if(strncmp(temp,"black",5) == 0)
				*b = true;	
			else if(strncmp(temp,"white",5) == 0)
				*b = false;	
			else{
				fprintf(stderr,"Invalid order \n"); break; }			
	
				
		}else if(i == 2){
					
			if(strncmp(temp,"swapon",6) == 0)
				*swap_on = true;	
			else if(strncmp(temp,"swapoff",7) == 0)
				*swap_on = false;
			else{
				fprintf(stderr,"Invalid order \n"); break; }	
		
				
		}else if( i == 3){
					
			*size = atoi(temp);
					
			if( (*size < 4) || (*size > 26) ){
				fprintf(stderr,"Size must be between [4,26].Size has been set to 11 \n");  *size = 11; }		
		}
					
		temp = strtok(NULL," ");			
	}
	
	
}


void save_in_file(char buffer[],int size,char ch,char **A){
	
	int i,j;
	char *temp;
	FILE *ifp;
	
	temp = strtok(buffer+5,"\n");			/* �� ����� ��� ������� ������� ��� �� buffer[5] ��� ������������ ��� temp */
							
	if((ifp = fopen(temp,"w")) == NULL)
		fprintf(stderr,"There was an error opening the file \n");
		
	putc(size,ifp);
	putc(ch,ifp);
			
	for(i=0 ; i < size ; i++)
		for(j=0 ; j < size ; j++)
			if (A[i][j] == ' ')
				putc('n',ifp);
			else if(A[i][j] == 'w')
				putc('w',ifp);
			else
				putc('b',ifp);		
		
	fclose(ifp);	
						
}





