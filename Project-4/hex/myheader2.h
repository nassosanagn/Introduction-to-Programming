

void showstate(const int size,char **A);

int play(Listptr *ptrlisthead,char buf[],int size,char ch,char **A);

int swap(Listptr listhead,bool swap_on,int counter,char **A);

void newgame(char buffer[],int *size,bool *b,bool *swap_on);		/* Η συνάρτηση επιστρέφει τα στοιχεία του νέου παιχνιδιού μέσω δεικτών */

void save_in_file(char buffer[],int size,char ch,char **A);
