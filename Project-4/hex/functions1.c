
#include "myheader1.h"

void insert_at_start(Listptr *ptraddr,int number,int letter){

Listptr templist;
		

 templist = *ptraddr; 
 
 *ptraddr = malloc(sizeof(struct listnode));
  
  (*ptraddr)->number = number;  
  (*ptraddr)->letter = letter;
  (*ptraddr)->next = templist; 

}


void delete_first_node(Listptr *ptraddr,char **A){
	
Listptr temp;
	
	
	if(*ptraddr == NULL){
		fprintf(stderr,"There is no move to undo \n"); return; }	
	
	A[(*ptraddr)->number][(*ptraddr)->letter] = ' ';			/* �� ����� ��� ������ ��� ���������� ��������� '�����������' */
	temp = *ptraddr;
	*ptraddr = temp->next;
	free(temp);
	
}


int mikos(int i,int j,const char ch,int size,bool flagw,bool flagb,char **A){
	
int number = 0;
int k = 0;
	
	
	if(ch == 'w'){
		if(i==0)							/* ���� ��������� ���� ���������� �� ����� (����-����) ��� ������ ������ �������� ��� ������ */
			flagw = true;
		
		if((i+1 == size)&&(flagw == true)){
				printf("\nEnd of game\n");
				printf("White player won\n");
				exit(0); 
				}
	}
			
	if(ch == 'b'){
		
		if(j == 0)					/* ���� ��������� ���� ���������� �� ����� ��� ������ ������ (�����-��������) �������� ��� ������ */
			flagb = true;
			
		if((j+1 == size)&&(flagb == true)){
			printf("\nEnd of game\n");
			printf("Black player won\n");
			exit(0);
		}
	}
	
	
	if(i == 0){
		
		if(j !=0 ){
			
			if(A[i][j-1] == ch){
				
				if(k>0)			/* ���� �� k ����� > 0 �������� ��� �� ������������ ������� ���� ��� �������� ����� */
					number--;	/* ��� �� number ���������� 1 ���� ��� �������� �� ��������� */
					
				A[i][j]  = '!';
				number += mikos(i,j-1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
			
			if(A[i+1][j-1] == ch){
				
				if(k>0)
					number--;
					
				A[i][j] = '!';
				number += mikos(i+1,j-1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
		}
		
		if(j+1 != size){
			if(A[i][j+1] == ch){
				
				if(k>0)
					number--;
					
				A[i][j]   = '!';
				number += mikos(i,j+1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
		}
			
		if(A[i+1][j] == ch){
			
			if(k>0)
				number--;
				
			A[i][j]   = '!';
			number += mikos(i+1,j,ch,size,flagw,flagb,A) + 1;
			k++;
		}
	
		
	}else if(i+1 == size){
		
		
			if( j != 0){
				if(A[i][j-1] == ch){
					
					if(k>0)
						number--;
					A[i][j]  = '!';
					number += mikos(i,j-1,ch,size,flagw,flagb,A) + 1;
					k++;
				}
			}
			
			if(j+1 != size){
				
				if(A[i-1][j+1] == ch){
					
					if(k>0)
						number--;
						
					A[i][j] = '!';
					number += mikos(i-1,j+1,ch,size,flagw,flagb,A) + 1;
					k++;
				}
				if(A[i][j+1] == ch){
					
					if(k>0)
						number--;	
					A[i][j]   = '!';
					number += mikos(i,j+1,ch,size,flagw,flagb,A) + 1;
					k++;
				}
			}
			
			if(A[i-1][j] == ch){
				
				if(k>0)
					number--;
				
				A[i][j] = '!';
				number += mikos(i-1,j,ch,size,flagw,flagb,A) + 1;
				k++; 
			}
		
		
		
	}else{		/* ���� ��������� ���� ���� �� i ��� ����� ��� ���� */
	
		
		if( j != 0){				/* ���� ��������� ���� �� j ����� 0 ��� ������ �� ����� ��� ���� j-1 */
		
			if(A[i+1][j-1] == ch){
				
				if(k>0)
					number--;
					
				A[i][j] = '!';
				number += mikos(i+1,j-1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
			
			if(A[i][j-1] == ch){
				
				if(k>0)
					number--;
					
				A[i][j]   = '!'; 
				number += mikos(i,j-1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
		}
		
		if( j+1 != size){		/* ���� ��������� ���� �� j ����� size-1 ��� ������ �� ����� ��� ���� size */
		
			if(A[i][j+1] == ch){
				
				if(k>0)
					number--;
					
				A[i][j] = '!';
				number += mikos(i,j+1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
			if(A[i-1][j+1] == ch){
				
				if(k>0)
					number--;
					
				A[i][j] = '!';
				number += mikos(i-1,j+1,ch,size,flagw,flagb,A) + 1;
				k++;
			}
		}
			
		if(A[i+1][j] == ch){
		
			if(k>0)
				number--;
			
			A[i][j] = '!';
			number += mikos(i+1,j,ch,size,flagw,flagb,A) + 1;
			k++;
		}
		
		if(A[i-1][j] == ch){
			
			if(k>0)
				number--; 
						
			A[i][j] = '!';
			number += mikos(i-1,j,ch,size,flagw,flagb,A) + 1;
			k++;
			
		}
		
	}
		
	if(A[i][j] == ch){		/* ��� �� �������� ��� ���� ��������� ��� �������� ��� ����������� ���� �� ������������ ����� ������� ��������*/
		A[i][j] = '!';
		return 1;
		
	}else{					/* ��� �� �������� ��� ���� ��������� ��� �������� ��� ����������� ��� �� ����� ��� �� ���� ���� */
		
	 	A[i][j] = '!';
		return number;	
	}
}



int utility(int *maxw,int *maxb,int size,char **A){
	
int i,j,k,l;
int w=0,b=0,MIN = 1000;
char **temp;
			
	temp = malloc(size * sizeof(char *));
			
	for(i=0 ; i < size ; i++)
		temp[i] = malloc(size * sizeof(char));
			
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			temp[i][j] = A[i][j];
						
					
	for(i=0 ; i < size ; i++){	
		for(j=0 ; j < size ; j++){
								
			
			if(temp[i][j] == 'w')
				w = mikos(i,j,'w',size,false,false,temp);
					
						
			if(temp[i][j] == 'b')	
				b = mikos(i,j,'b',size,false,false,temp);
					
			if( w > *maxw)
				*maxw = w;
						
			if( b > *maxb)
				*maxb = b;	
		
					
		for(k=0;k<size;k++)					/* ��������� ��� ������ A ���� ������ temp ���� ���� ���� � � �� �������� ��� ����� ��� */
			for(l=0;l<size;l++)
				temp[k][l] = A[k][l];
						
		}
	}
	
return 0;	
			
}






