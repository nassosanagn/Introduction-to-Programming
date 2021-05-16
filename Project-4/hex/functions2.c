
#include "myheader1.h"
#include "myheader2.h"

void showstate(const int size,char **A){
	
	int i,j,middle,spaces = 0;
	char ch = 'A';
	
	for(i=0; i<size ;i++){
		
		if(i == 0){	
		
			for(j=0 ; j < size/2 ; j++)		/* Εκτύπωση του WHITE στην αρχή */
				printf("    ");
			printf("W H I T E \n");
		
		
			printf("    ");	
			for(j=0 ; j < size ; j++)				/* Εκτύπωση των γραμμάτων A,B,C... στην αρχή */
				printf("  %c ",ch++);			
			printf("\n    ");
		
			for(j=0 ; j < size ; j++)
				printf("  _ " );
			printf("\n     ");
				
		
			for(j=0 ; j < size ; j++)
				printf("/ \\_");	
			printf("\n");
			
			spaces += 4;			/* Ο αριθμός των κενών απο την αρχή κάθε σειράς */
		}
		
		middle = (size/2)-1;				/* Η μέση του πλαισίου (περίπου) όπου θα εκτυπωθεί το BLACK και το WHITE */
		
		for(j=0 ; j< spaces-4 ; j++)
			printf(" ");		
		
		if(i == middle)
			printf("\b\bB ");
			
		else if(i == middle+1)
			printf("\b\bA ");
		
		else if(i == middle+2)
			printf("\b\bK ");
		
		
		if(i<9)						/* Εκτύπωση των αριθμών απο αριστερά , υπάρχει διαφορά αν ο αριθμός έχει 1 η 2 ψηφία οπότε όταν έχει 2 θα έχει ένα λιγότερο κενό */
			printf(" %d  ",i+1);
		else
			printf(" %d ",i+1);
					
				
		for(j=0 ; j < size ; j++)
			printf("| %c ",A[i][j]);
		printf("|");		
		printf("  %d",i+1);			/* Εκτύπωση των αριθμών απο δεξιά*/
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
	
	for(j=0 ; j <= spaces-2 ;j++)		/* Εκτύπωση των γραμμάτων A,B,C... στο τέλος */
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

	
	letter = buf[5] - 'A';		/* Ο 5ος στη σειρά χαρακτήρας είναι ο A,B,..*/
	number = atoi(buf+6);		/* Ο 6ος στη σειρά χαρακτήρας είναι ο αριθμός */
	
	if( (buf[5]<'A') || (buf[5]>'A'+size-1) || (number< 1) || (number>size) ){
		fprintf(stderr,"Error: Invalid coordinates \n");  
		return -1; 
	}
		
	if( A[number-1][letter] != ' '){
		fprintf(stderr,"Error: Move already played \n"); return -1;
	}else
		A[number-1][letter] = ch;					/* number -1 επειδη οι θέσεις του πίνακα είναι [0,size-1] και όχι [1,size] όπως φαίνεται στο σχήμα */		
	
	
	insert_at_start(listhead,number-1,letter);			/* Δημιουργείται λίστα για αποθήκευση των κινήσεων και κάθε νέα κίνηση καταχωρίζεται στην αρχή */
	
	printf("Move played: %c%d \n",buf[5],number);
	
	utility(&maxw,&maxb,size,A);		/* Η συνάρτηση χρησιμοποιείται για να ελέγξει εάν κέρδισε κάποιος παίκτης */
													
	return number;
}



int swap(Listptr listhead,bool swap_on,int counter,char **A){

	if(listhead->next != NULL){													/* επειδή το swap επιτρέπεται μόνο στη πρώτη κίνιση */
		fprintf(stderr,"This is not the first move \n"); return -1; }
		
	if(swap_on == false){
		fprintf(stderr,"The swap rule is not active \n"); return -1; }
			
	int temp1,temp2;
			
	temp1 = listhead->number;
	temp2 = listhead->letter;
			
	delete_first_node(&listhead,A);			/* Διαγράφεται ο 1ος κόμβος που είχε την κίνηση του λευκού παίκτη */
			
	insert_at_start(&listhead,temp2,temp1);		/* και γίνεται αντικατάσταση με την συμμετρική κίνηση απο τον μαύρο παίκτη */ 
			
	A[temp2][temp1] = 'b';
	
	return 0;
}


void newgame(char buffer[],int *size,bool *b,bool *swap_on){			/* Η συνάρτηση επιστρέφει τα στοιχεία του νέου παιχνιδιού μέσω δεικτών */

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
	
	temp = strtok(buffer+5,"\n");			/* Το όνομα του αρχείου αρχίζει απο το buffer[5] και αντιγράφεται στο temp */
							
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





