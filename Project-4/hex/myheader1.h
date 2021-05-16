
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct listnode *Listptr;

void insert_at_start(Listptr *ptraddr,int number,int letter);			/* Η συνάρτηση προσθέτει την νεότερη κίνηση στην αρχή της λίστας */

void delete_first_node(Listptr *ptraddr,char **A);						/* Η συνάρτηση διαγράφει τον πρώτο κόμβο και την νεότερη κίνηση απο τον πίνακα π.χ. σε περίπτωση undo */

int mikos(int i,int j,const char ch,int size,bool flagw,bool flagb,char **A);	/* Η συνάρτηση επιστρέφει το μήκος για την μεγαλύτερη ακολουθία που περιλαμβάνει συγκεκριμένο πλακίδιο */

int utility(int *maxw,int *maxb,int size,char **A);		/* Η συνάρτηση βρίσκει τη μεγαλυτερη ακολουθία από συνεχόμενα πλακίδια του κάθε παίκτη και επίσης βρίσκει αν τελείωσε το παιχνίδι*/


struct listnode{					/* Η λίστα αποθηκεύει τις κινήσεις που έχουν παιχτεί */
	int number;
	int letter;
	Listptr next;
};
