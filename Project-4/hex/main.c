/* File: hex.c */

#include "myheader1.h"
#include "myheader2.h"


int main(int argc,char *argv[]){
	
	int counter=0;
	int size = 4;									/* Αν δεν δοθεί επιλογή για size τοτε είναι 11 */
	int i,j,number, difficulty = 1;
	char buffer[30],ch,**A;
	bool b = false , swap_on = false;		/* οταν b = true ο χρήστης είναι ο μαύρος παίκτης */
	Listptr listhead = NULL;
	
	memset(buffer,'\0',sizeof(buffer));					/* 'Καθαρισμός' του πίνακα buffer */
	
	if(argc > 7){											/* Στην περίπτωση που δοθούν περισσότερα ορίσματα στην γραμμή εντολών */
		fprintf(stderr,"Too many arguments. \n");	exit(2); }
	
	for(i=1 ; i < argc ; i++){
		
		if(strcmp(argv[i],"-b") == 0)				/* Στην περίπτωση όπου ο χρήστης δώσει την επιλογή -b, θα είναι ο μαύρος παίκτης */
			b = true;
			
		if(strcmp(argv[i],"-n") == 0){				/* Στην περίπτωση όπου ο χρήστης δώσει την επιλογή -n, για να ορίσει το μέγεθος του πλαισίου */
		
			size = atoi(argv[i+1]);
			
			if( (size<4) || (size>26) ){
				fprintf(stderr,"Size must be between [4,26].Size has been set to 11 \n");	size = 11; }
				
			i++;
		}
		
		if(strcmp(argv[i],"-s") == 0)				/* Στην περίπτωση όπου ο χρήστης δώσει την επιλογή -s, για να ενεργοποιήσει τον κανόνα ανταλλαγής */
			swap_on = true;
		
		if((strcmp(argv[i],"-d") == 0)){			/* Στην περίπτωση όπου ο χρήστης δώσει την επιλογή -d, για να ορίσει την δυσκολία του παιχνιδιού */
			difficulty = atoi(argv[i+1]);
			i++;
		}	
	}
	
	
	A = malloc(size * sizeof(char *));					/* Δημιουργία Πίνακα */
	
	if(A == NULL){
		fprintf(stderr,"Sorry, cannot allocate memory \n");	exit(2); }
	

	for(i=0 ; i < size ; i++){
		
		A[i] = malloc(size * sizeof(char));	
		
		if(A[i] == NULL){
			fprintf(stderr,"Sorry, cannot allocate memory \n");	exit(2); }			
	}
	
	for(i=0 ; i < size ; i++)				/* Αρχικοποίηση Πίνακα σε ' ' */
		for(j=0 ; j < size ; j++)
				A[i][j] = ' ';
			
	
	while(1){					/* Βρόγχος για επιλογή εντολών */
	
	
		if(counter%2 == 0 ){
			printf( (b) ? "White player (computer) plays now \n" : "White player (human) plays now \n");
			ch = 'w';
		}else{
			printf( (b) ? "Black player (human) plays now \n" : "Black player (computer) plays now \n");
			ch = 'b';
		}	
			
		printf("> ");
		
		fgets(buffer,30,stdin);
		
		if (strcmp(buffer,"quit\n") == 0){																			/* Στην περίπτωση όπου επιλέχτηκε quit */
		
			printf("\nThank you for playing! \n"); 
			exit(2); 
		
		}else if (strcmp(buffer,"cont\n") == 0){
			
			
			if(b == true){																/* Όταν b = false και counter άρτιος είναι η σειρά του χρήστη, όπου δεν επιτρέπεται η εντολή cont */
				if(counter%2 != 0 ){
					fprintf(stderr,"This is not the computer's turn \n"); continue; }
			}else
				if(counter%2 == 0 ){													/* Όταν b = true και counter περιττός είναι η σειρά του χρήστη όπου δεν επιτρέπεται η εντολή cont */
					fprintf(stderr,"This is not the computer's turn \n"); continue; }
			
			int tempx,tempy;
			int maxw=0,maxb=0;
			int min = 1000;
			
			for(i=0; i < size ; i++)
				for(j=0 ; j < size ; j++){
					
						if(A[i][j] == ' ')
							A[i][j] = ch;
						else
							continue;
							
						utility(&maxw,&maxb,size,A);
						
						A[i][j] = ' ';
						
					if(maxb - maxw < min){
						min = maxb - maxw;
						tempx = i;
						tempy = j;	
						
					}
				}
			
			insert_at_start(&listhead,tempx,tempy);
			
			A[tempx][tempy] = ch;
			
			printf("Move played: %c%d \n",tempy+'A',tempx+1);
		
		
		
		}else if (strcmp(buffer,"suggest\n") == 0){
			
			
			if(b == false){															/* Η εντολή suggest είναι αποδεκτή μόνο όταν είναι η σειρά του χρήστη */
				if(counter%2 != 0 ){
					fprintf(stderr,"This is not the human's turn \n"); continue; }
			}else
				if(counter%2 == 0 ){
					fprintf(stderr,"This is not the human's turn \n"); continue; }
		
			int tempx,tempy;
			int maxw=0,maxb=0;
			int min = 1000;
				
				for(i=0; i < size ; i++)
					for(j=0 ; j < size ; j++){
						
							if(A[i][j] == ' ')
								A[i][j] = ch;
							else
								continue;
								
							utility(&maxw,&maxb,size,A);
							
							A[i][j] = ' ';
							
						if(maxw - maxb < min){
							min = maxw - maxb;
							tempx = i;
							tempy = j;	
							
						}
					}
					
			printf("You may play at %c%d \n",tempy+'A',tempx+1);
			
			continue;		
			
		
		}else if(strncmp(buffer,"newgame",7) == 0){
			
			int temp_size = size;
				
			newgame(buffer,&size, &b ,&swap_on);

			counter = 0;
			
			while(listhead != NULL)					/* ’δειασμα του πίνακα και των κινήσεων (δηλαδή της λίστας) για νέο παιχνίδι */
				delete_first_node(&listhead,A);
			
			for(i=0 ; i < temp_size ; i++)			/*Αποδέσμευση μνήμης του προηγούμενου πίνακα */
				free(A[i]);
			free(A);
			
			A = malloc(size * sizeof(char *));							/* Δημιουργία νέου πίνακα */
	
			if(A == NULL){
				fprintf(stderr,"Sorry, cannot allocate memory \n");	exit(2); }
			
			for(i=0 ; i < size ; i++){
				
				A[i] = malloc(size * sizeof(char));	
				
				if(A[i] == NULL){
					fprintf(stderr,"Sorry, cannot allocate memory \n");	exit(2); }			
			}
			
			for(i=0 ; i < size ; i++)
				for(j=0 ; j < size ; j++)
						A[i][j] = ' ';

		continue;
		
		}else if (strcmp(buffer,"showstate\n") == 0){																/* Στην περιπτωση οπου επιλέχτηκε showstate */
		
			showstate(size,A);	
			continue;			   	/* Ο χρήστης ξαναπαίζει αν επιλέξει να εκτυπωθεί η κατάσταση */
		
			
		}else if(strncmp(buffer,"play",4) == 0){																	/* Στην περίπτωση όπου επιλέχτηκε play */
		
				
			if( play(&listhead,buffer,size,ch,A) == -1)						/* Η συνάρτηση επιστρέφει -1 σε περίπτωση λάθους */
				continue;			/* Γιατί αν ο χρήστης δώσει μη έγκυρες συντεταγμένες ή πληκτρολογήσει λάθος ξαναπαίζει (δηλαδη το counter δεν αυξανεται) */
					
		}else if (strcmp(buffer,"undo\n") == 0){																			/* Στην περίπτωση όπου επιλέχτηκε undo κάθε φορά διαγράφεται*/
		
			if(b == false){																								/* το πρώτο στοιχείο της λίστας, άρα και η κίνηση */
																			
				if	(counter%2 == 0 ){								/* Αν έχει παίξει ο υπολογιστής διαγράφοναι 2 κινήσεις αλλιώς 1 */							
					delete_first_node(&listhead,A);
					delete_first_node(&listhead,A);					/* Σε κάθε περίπτωση θα είναι η σειρά του χρήστη */
					
				}else{
					delete_first_node(&listhead,A);
				
				}
				counter = 2;
			
			}else{
				if(counter%2 == 0 )
					delete_first_node(&listhead,A);	
				else{
					delete_first_node(&listhead,A);
					delete_first_node(&listhead,A);
				}													
				counter = 3;		
		}
		
		continue;
					
		}else if(strncmp(buffer,"level",5) == 0){																			/* Στην περίπτωση όπου επιλέχτηκε level */
		
		
			if((buffer[6] >= '0')&&(buffer[6] <= '9')){
				
				if(buffer[5] != 32){
					fprintf(stderr,"No space character given \n"); continue; }
					
				difficulty = atoi(buffer+6);
				printf("The level of difficulty has been set to %d \n",difficulty);
				
			}else		
				printf("The level of difiiculty is %d \n",difficulty);
									
			continue;
			
			
			
		}else if (strcmp(buffer,"swap\n") == 0){																	/* Στην περίπτωση όπου επιλέχτηκε η εντολή swap */
		
		 if(swap(listhead,swap_on,counter,A) == -1)		/* Αν η swap επιστρέψει -1 τότε έγινε λάθος και παίζει ο ίδιος παίκτης */
			continue;

		}else if(strncmp(buffer,"load",4) == 0){															/* Στην περίπτωση όπου επιλέχτηκε να γίνει load απο αρχείο */
		
			char *temp,ch2;
			FILE *ifp;
						
			temp = strtok(buffer+5,"\n");		
			
			if((ifp = fopen(temp,"r")) == NULL)
				fprintf(stderr,"There was an error opening the file \n");
				
			for(i=0 ; i < size ; i++)		/*Αποδέσμευση του προηγούμενου πίνακα */
				free(A[i]);
			free(A);		
				
			size = getc(ifp);				/* Η διάσταση του πίνακα */
			
			A = malloc(size * sizeof(char *));					/* Δημιουργία νέου πίνακα */

			if(A == NULL){
				fprintf(stderr,"Sorry, cannot allocate memory \n");	exit(2); }
		
			for(i=0; i < size ; i++){
				
					A[i] = malloc(size * sizeof(char));	
					if(A[i] == NULL){
						fprintf(stderr,"Sorry, cannot allocate memory \n");	exit(2); }			
			}
			
			if(getc(ifp) == 'w')		/* Αν το counter είναι άρτιος παίζει ο λευκός παίκτης, αλλιώς ο μαύρος */
				counter = 2;
			else
				counter = 3;	
		
			for(i=0 ; i < size ; i++)
				for(j=0 ; j < size ; j++){
					ch2 = getc(ifp);
					if(ch2 == 'n')
						A[i][j] = ' ';
					else if(ch2 == 'w')
						A[i][j] = 'w';
					else
						A[i][j] = 'b';						
				}
			
			fclose(ifp);		
			continue;
			
			
		}else if(strncmp(buffer,"save",4) == 0){																/* Στην περίπτωση όπου επιλέχτηκε να γίνει save σε αρχείο */
			
			save_in_file(buffer,size,ch,A);
			continue;
							
		}else{																									/* Στην περίπτωση όπου δοθεί μη έγκυρη εντολή */
		
			fprintf(stderr,"Invalid order \n");
			continue;
		}
					
		counter++;
			
		fflush(stdin);	
	}	
	
return 0;
}

