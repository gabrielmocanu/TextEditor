// functie ce adauga la sfarsitul unei liste un nod 
void AddNodLast(char letter, Nod **head)
{
	Nod *current = (Nod *)malloc(sizeof(Nod));
	Nod *last = *head;
	current -> letter = letter;
	current -> next = NULL;
	if( *head == NULL )
	{
		current -> prev = NULL;
		*head = current;
		return;
	}
	while(last -> next != NULL)
	{
		last = last -> next;
	}
	last -> next = current;
	current -> prev = last;
	return;
}

// functie de adauga la sfarsitul unei liste de liste un nod
void Addlist(list **head, Nod *here,int line,int column)
{
	list *new_nod = (list *)malloc(sizeof(list));
	list *last = *head;
	Nod *current = here;
	new_nod -> lin = line;
	new_nod -> col = column;
	new_nod -> pas = NULL;
	while(current != NULL)
	{
		AddNodLast(current->letter,&new_nod->pas);
		current = current ->next;
	}
	new_nod -> next = NULL;
	if(*head == NULL)
	{
		new_nod -> prev = NULL;
		*head = new_nod;
		return ;
	}
	while(last -> next != NULL)
		last = last -> next;
	last -> next = new_nod;
	new_nod -> prev = last;
	return;
}

// functie ce returneaza numarul de noduri al unei liste 
int SizeOf(Nod *head)
{
	int lenght = 0;
	Nod *current = head;
	while(current != NULL)
	{
		lenght++;
		current = current -> next;
	}
	return lenght;
}

// functie de afisare a listei
void print(Nod *head)
{
	Nod *current = head;

	while(current != NULL)
	{
		printf("%d",current->letter);
		current = current -> next; 
	}
}

//functie de afisare a listei de liste
void printList(list *head)
{
	list *current = head;
	while(current != NULL)
	{
		print(current -> pas);
		printf("\n");
		printf("%d %d",current -> lin,current -> col);
		printf("\n");
		current = current -> next;
	}
	return;
}


// functie de stergere a unui nod reprezentand o lista dintr-o lista de liste de la o anumita pozitie data 
void deleteNodeList(list **head,int poz)
{
	int i = 1;
	list *current = *head;
	while(i < poz)
	{
		current = current -> next;
		i++;
	}
	if(current == NULL)
    	return ;
	if(current -> next != NULL)
		current -> next -> prev = current -> prev;

	if(current -> prev != NULL)
		current -> prev -> next = current -> next;

	free(current);
}

// functie de stergere a unui nod dintr-o lista dublu inlantuita de la o anumita pozitie data
void deleteNodePos( Nod** head, int n)
{
	int i = 1;
	Nod* current = *head;
    if (*head == NULL || n <= 0)
        return;
    while(i < n)
    {
        current = current->next;
        i++;
    }
    if(current == NULL)
    	return ;
    if(*head == current)
    	*head = current -> next;
    if (current->next != NULL)
        current->next->prev = current->prev;

    if (current->prev != NULL)
        current->prev->next = current->next;
    free(current);
}

// functie de adaugare intr-o lista dublu inlantuita la o anumita pozitie data
void AddNodePos(int position,char letter,Nod **head)
{
	int i;
	Nod *current1;
	Nod *current2;
	Nod *current = (Nod *)malloc(sizeof(Nod));
	current -> letter = letter;
	if(*head==NULL && position==1)
	{
		current->prev=current->next=NULL;
		*head = current;
		return;
	}
	if(position == 1)
	{
		(*head)-> prev = current;
		current -> prev = NULL;
		current -> next = *head;
		*head = current;
		return;
	}
	current1 = *head;
	for(i=1;i<position-1;i++)
		current1 = current1 -> next;
	current -> next = current1 -> next;
	current -> prev = current1;
	current1 -> next = current;
	if(current -> next != NULL)
	{
		current2 = current -> next;
		current2 -> prev = current;
	}
}

// functie de adaugare intr-o lista de liste a unui nod reprezentand o lista la o anumita pozitie data
void AddlistAtPosition(int position, list **head, Nod *here,int line, int column)
{
	int i;
	list *current1;
	list *current2;
	list *new_nod = (list *)malloc(sizeof(list));
	Nod *current = here;
	new_nod -> lin = line;
	new_nod -> col = column;
	new_nod -> pas = NULL;
	while(current != NULL)
	{
		AddNodLast(current->letter,&new_nod->pas);
		current = current ->next;
	}
	if(*head == NULL && position==1)
	{
		new_nod -> prev = new_nod -> next = NULL;
		*head = new_nod;
		return ;
	}
	if(position == 1)
	{
		(*head)->prev = new_nod;
		new_nod -> prev = NULL;
		new_nod -> next = *head;
		*head = new_nod;
		return ;
	}
	current1 = *head;
	for(i=1;i<position-1;i++)
		current1 = current1 -> next;
	new_nod -> next = current1 -> next;
	new_nod -> prev = current1;
	current1 -> next = new_nod;
	if(new_nod -> next != NULL)
	{
		current2 = new_nod -> next;
		current2 -> prev = new_nod;
	}
}

// functie de stergere a unei liste dublu inlantuite
void deleteList(Nod** head)
{
   Nod* current = *head;
   Nod* next;
 
   while (current -> next!= NULL) 
   {
       next = current->next;
       current = next;
       free(current);
   }
  	*head = NULL;
}

// functia pentru modul de inserare 
void INSERT(char *line_read,int *poz_lin,int *poz_col,Nod **lista_fisier,int *nr_operation_aux)
{
	char c; // caracterul pe care il citim
	int i = 0;
	int nr_col=1; // pornim mereu de la coloana 1 si linia 1
	int nr_lin=1;
	int nr_char_all = 1; // numarul de caractere care se afla deja in lista
	Nod *current = *lista_fisier;
	while(current != NULL)
	{
		if(nr_lin == *poz_lin) // in caz ca avem text deja inserat trebuie sa ajungem pana la linia curenta
			break;
		if(current -> letter == '\n') // numaram liniile
			nr_lin++;
		current = current -> next;
		nr_char_all++;
	}
	while(nr_col < *poz_col) // in cazul in care cursorul nu se afla la inceput de rand trebuie sa numaram caracterele pana la cursor
	{
		current = current -> next;
		nr_col++;
		nr_char_all++;
	}
	while (i < strlen(line_read))
	{
		c = line_read[i]; // luam fiecare caracter din linia citita 
		AddNodePos(nr_char_all,c,lista_fisier); // il adaugam in lista
		i++;
		nr_char_all++;
	}
	(*poz_col) = 1; // pozitia pe coloana dupa inserare va fi mereu 1
	(*poz_lin)++; // incrementam pozitia pe linii
	(*nr_operation_aux)++; // incrementam numarul de operatii facut in insert
}

// functie pentru cazul in care nu salvam, trebuie numerotate operatiile
void not_save(int *nr_operation, int *nr_operation_aux, int *nr_operation_for_save)
{
	(*nr_operation)++; // incrementam numarul total de operatii
	if(*nr_operation_aux >= 1) // in cazul in care s-a facut o operatie/mai multe operatii 
	{							// de insert inainte si au fost intercalate comenzi vom numara insertul ca fiind o singura comanda
		(*nr_operation)++;
		*nr_operation_aux = 0;
	}
	(*nr_operation_for_save)++; // incrementam numarul de operatii ce verifica daca lista trebuie salvata in fisier sau nu

}

// functie pentru operatia de go to line [parametru]
void go_to_line(int *poz_lin,int *poz_col)
{
	char *arg1;
	arg1 = strtok(NULL,"\n"); // luam argumentul dat operatiei
	*poz_lin = atoi(arg1); // vom duce cursorul pe linia argumentului dat si pe coloana 1
	*poz_col = 1;
}

// functie pentru operatia de go to char [parametru][parametru]
void go_to_char(int *poz_lin,int *poz_col)
{
	char *arg1,*arg2;
	arg1 = strtok(NULL," "); // luam primul argument dat operatiei
	*poz_col = atoi(arg1); // vom duce cursorul pe coloana specificata de parametru
	arg2 = strtok(NULL," "); // luam al doilea argument dat operatiei [optional]
	if(arg2 == NULL)
		return;	
	*poz_lin = atoi(arg2); // vom duce cursorul pe linia specificata de parametru
}

// functie pentru operatia de backspace
void backspace(Nod **lista_fisier,int *poz_lin,int *poz_col)
{
	int nr_poz=1; // variabila pentru pozitionarea cursorului pe aceasta pozitie si stergerea elementului de dinainte
	int nr_col=1; // variabila pentru numarul de caractere de la inceputul liniei pana la pozitia la care trebuie sa ajungem
	int nr_lin=1; // variabila pentru numarul de linii pe care il parcurgem
	int nr_lin_prev = 1; // variabila prin care ajungem la linia de dinaintea stergerii (b), in cazul in care vom sterg \n
	int char_prev_line = 1;  // numarul de caractere de dinainte de \n in cazul in care il vom sterge pe aceasta
	Nod *current = *lista_fisier;
	Nod *current2 = *lista_fisier;
	while(current != NULL) // parcurgem lista pentru a ajunge pe linia unde e cursorul, numarand pozitiile
	{
		if(nr_lin == *poz_lin)
			break;
		if(current -> letter == '\n')
			nr_lin++;
		current = current -> next;
		nr_poz++;
	}
	while(nr_lin_prev < nr_lin-1 && current2 != NULL) // parcurgem lista pentru a ajunge pe linia de dinainte
	{
	 	if(current2 -> letter == '\n')
	 		nr_lin_prev++;
	 	current2 = current2 -> next;
	}
	while(current2 != NULL && current2 -> letter != '\n' ) // parcurgem lista pentru a determina numarul de caractere al liniei de dinainte
	{
		char_prev_line++;
		current2 = current2 -> next;
	}
	while(nr_col < *poz_col) // parcurgem lista pentru a ajunge pe coloana unde e cursorul, numarud pozitiile
	{
		current = current -> next;
		nr_col++;
		nr_poz++;
	}
	deleteNodePos(lista_fisier,nr_poz-1);// prin apelarea backspace se sterge caracterul de dinaintea cursorului, deci vom sterge un nod de pe pozitia nr_poz -1
	if(*poz_col > 1) // daca cursorul se afla pe o pozitie mai mare decat 1 pe coloane, atunci miscam cursorul la stanga
		(*poz_col)--;
	else   // daca este pe pozitia 1 atunci mutam cursorul cu o linie mai sus pe ultimul caracter
	{
		(*poz_lin)--;
		*poz_col = char_prev_line;
	}

}

// functie pentru operatia de delete line [parametru]
void delete_line(Nod **lista_fisier,int *poz_lin,int *poz_col)
{
	int nr_lin = 1; // variabila pentru numarul de linii pe care il parcurgem
	int nr_poz = 1; // variabila pentru pozitionarea cursorului pe aceasta pozitie si stergerea elementului de dinainte
	int line_delete; // linia ce va fi stearsa
	int char_deleted = 0; // numarul de caractere pe care il vom sterge
	int i = 0;
	char *arg1; // argumentul comenzii
	Nod *current = *lista_fisier;
	arg1 = strtok(NULL,"\n");
	if(arg1 == NULL) // daca nu se da un anumit argument se va sterge linia curenta
	{
		line_delete = *poz_lin; // linia ce va fi stearsa este linia curenta
		while(current != NULL ) // parcurgem lista pentru a ajunge pe linia unde e cursorul, numarand pozitiile
		{
			if(nr_lin == line_delete)
				break;
			if(current -> letter == '\n')
				nr_lin++;
			current = current -> next;
			nr_poz++;
		}
		while(current -> letter != '\n' && current -> next != NULL) // calculam numarul de caractere ce vor fi sterse de pe linie
		{
			char_deleted++;
			current = current ->next;
		}
		char_deleted++; // adaugam \n
		while(i < char_deleted ) // stergem toate nodurile de pe linia curenta ce trebuie stearsa
		{
			 deleteNodePos(lista_fisier,nr_poz);
			 i++;
		}
		if(current -> letter == '\n') // stergem \n de la sfarsitul liniei
			deleteNodePos(lista_fisier,nr_poz);
		*poz_col = 1; // mutam cursorul pe coloana 1 si pe linia anterioara
		(*poz_lin)--;
	}
	else
	{
		line_delete = atoi(arg1);
		while(current != NULL )  // parcurgem lista pentru a ajunge pe linia unde e cursorul, numarand pozitiile
		{
			if(nr_lin == line_delete)
				break;
			if(current -> letter == '\n')
				nr_lin++;
			current = current -> next;
			nr_poz++;
		}
		while(current -> letter != '\n') // stergem toate nodurile de pe linia ce trebuie stearsa
		{
			deleteNodePos(lista_fisier,nr_poz);
			current = current -> next;
		}
		deleteNodePos(lista_fisier,nr_poz);
		*poz_col = 1; // mutam cursorul pe coloana 1 si pe linia anterioara
		(*poz_lin)--;
	}
}

// functie pentru operatia de delete char [parametru]
void delete_char(Nod **lista_fisier,int *poz_lin,int *poz_col)
{
	char *arg1;
	int i;
	int nr_lin = 1; // variabila pentru numarul de linii pe care il parcurgem
	int nr_col = 1; // variabila pentru numarul de caractere de la inceputul liniei pana la pozitia la care trebuie sa ajungem
	int nr_poz = 1; // variabila pentru pozitionarea cursorului pe aceasta pozitie si stergerea elementului de dinainte
	int char_delete; // retine linia ce va fi stearsa
	arg1 = strtok(NULL,"\n");
	Nod *current = *lista_fisier;
	if(arg1 == NULL) // daca nu se da niciun argument
	{
		char_delete = 1; // se va sterge un singur caracter
		while(current != NULL) // parcurgem lista pentru a ajunge pe linia unde e cursorul, numarand pozitiile
		{
			if(nr_lin == *poz_lin)
				break;
			if(current -> letter == '\n')
				nr_lin++;
			current = current -> next;
			nr_poz++;
		}
		while(nr_col < *poz_col) // parcurgem lista pentru a ajunge pe coloana unde e cursorul, numarud pozitiile
		{
			current = current -> next;
			nr_col++;
			nr_poz++;
		}
		deleteNodePos(lista_fisier,nr_poz); // stergem caracterul
	}
	else
	{
		char_delete = atoi(arg1);
		while(current != NULL) // parcurgem lista pentru a ajunge pe linia unde e cursorul, numarand pozitiile
		{
			if(nr_lin == *poz_lin)
				break;
			if(current -> letter == '\n')
				nr_lin++;
			current = current -> next;
			nr_poz++;
		}
		while(nr_col < *poz_col)  // parcurgem lista pentru a ajunge pe coloana unde e cursorul, numarud pozitiile
		{
			current = current -> next;
			nr_col++;
			nr_poz++;
		}
		for(i=0;i<char_delete;i++)
			deleteNodePos(lista_fisier,nr_poz); // stergem caracterele
	}
}

// functie pentru salvarea, suprascriem mereu in fisier la fiecare comanda de salvare sau la 5 operatii diferite
void save(FILE *fid, Nod **lista_fisier,int *nr_operation_for_save)
{
	Nod *current = *lista_fisier;
	while(current != NULL)
	{
		fprintf(fid,"%c",current->letter);
		current = current -> next;
	}
	fclose(fid);
	*nr_operation_for_save = 0;
}

// functie pentru operatia de undo
void undo(Nod **lista_fisier,list **istoric,list **redo,int *nr_of_undos,int *nr_operation,int *poz_lin,int *poz_col)
{
	int PositionOfLastCopy; // pozitia ultimului caracter din lista de caractere
	int NodesCopied = 0; // cate caractere vom copia in lista de caractere
	int lenght = 0; // lungimea unei liste
	int size;  // Numarul de caractere 
	Nod *temporar;
	Nod *current = *lista_fisier;
	list *current_list = *istoric;
	(*nr_of_undos)++; // incrementam numarul de undo-uri efectuate
	if(*nr_of_undos >= *nr_operation - *nr_of_undos) // in cazul in care sunt mai multe undo-uri decat operatii atunci fisierul trebuie sa fie gol
	{
		deleteList(lista_fisier); // stergem lista
		*poz_col = 1; // pozitionam cursorul pe prima pozitie
		*poz_lin = 1;
		Addlist(redo,current_list -> pas, current_list -> lin,current_list -> col); // adaugam aceasta stare in lista pentru redo
		return;
	}
	while(current_list != NULL) // calculam lungimea listei de istoric
	{
		current_list = current_list -> next;
		lenght++;
	}
	current_list = *istoric; 
	while(current_list -> next != NULL ) // ne deplasam pe ultima pozitie a istoricului
		current_list = current_list -> next;
	Addlist(redo,current_list -> pas, current_list -> lin,current_list -> col); // adaugam aceasta stare in lista de redo pentru a putea reveni la ea
	current_list = current_list -> prev; // ne intoarcem cu o stare in lista de istoric
	deleteNodeList(istoric,lenght); // stergem ultimul nod din lista de istoric
	temporar = current_list -> pas; // Copiem din lista de istoric in lista de caractere ce o retinem in fisier
	while(temporar != NULL)
	{
		NodesCopied++;
		if(current != NULL)
		{
			current -> letter = temporar -> letter;
			current = current -> next;
		}
		else
		{
			AddNodLast(temporar -> letter,lista_fisier);
		}
		temporar = temporar -> next;
	}
	*poz_lin = current_list -> lin; // Pozitionam cursorul unde era in starea anterioara
	*poz_col = current_list -> col;
	size = SizeOf(*lista_fisier);
	PositionOfLastCopy = NodesCopied;
	// In cazul in care revenim la o stare care are mai putine caractere decat starea curenta trebuie sa stergem toate caracterele ramase in plus
	// astfel noi trebuie sa retinem cate caractere am copiat si numarul de caractere din lista
	while(size > NodesCopied)
	{
	 	deleteNodePos(lista_fisier,PositionOfLastCopy+1);
	 	NodesCopied++;
	}
}

// functie pentru operatia de redo
void redo_operation(Nod **lista_fisier,list **istoric,list **redo,int *nr_of_redos,int *poz_lin,int *poz_col)
{
	int NodesCopied = 0; // cate caractere vom copia in lista de caractere
	int lenght = 0;
	int lenght2 = 0;
	int size; // Numarul de caractere 
	int PositionOfLastCopy;  // pozitia ultimului caracter din lista de caractere
	Nod *temporar;
	Nod *current = *lista_fisier;
	list *current_list = *redo;
	list *current2_list = *istoric;
	(*nr_of_redos)++; // incrementam numarul de redo-uri
	while(current2_list != NULL) // calculam numarul de elemente din istroic
	{
		current2_list = current2_list -> next;
		lenght2++;
	}
	if(*nr_of_redos > 1) // adaugam in lista de istoric dupa ce am ajuns la un anumit nivel cu redo
		AddlistAtPosition(lenght2 - *nr_of_redos + 2,istoric,current,*poz_lin,*poz_col);

	while(current_list != NULL) // calculam numarul de elemente din lista de redo
	{
		current_list = current_list -> next;
		lenght++;
	}
	current_list = *redo;
	while(current_list -> next != NULL) // ne deplasam pe ultimul element din redo
		current_list = current_list -> next;
	temporar = current_list -> pas;
	while(temporar != NULL) // Copiem din lista de redo in lista de caractere ce o retinem in fisier
	{
		NodesCopied++;
		if(current != NULL)
		{
			current -> letter = temporar -> letter;
			current = current -> next;
		}
		else
		{
			AddNodLast(temporar -> letter,lista_fisier);
		}
		temporar = temporar -> next;
	}
	*poz_lin = current_list -> lin; // Pozitionam cursorul unde era in starea anterioara
	*poz_col = current_list -> col;
	// In cazul in care revenim la o stare care are mai putine caractere decat starea curenta trebuie sa stergem toate caracterele ramase in plus
	// astfel noi trebuie sa retinem cate caractere am copiat si numarul de caractere din lista
	size = SizeOf(*lista_fisier);
	PositionOfLastCopy = NodesCopied;
	while(size > NodesCopied)
	{
	 	deleteNodePos(lista_fisier,PositionOfLastCopy+1);
	 	NodesCopied++;
	}
	deleteNodeList(redo,lenght); // stergem starea la care am trecut din redo
}

// functie pentru operatia de replace
void replace(Nod **lista_fisier,int *poz_lin,int *poz_col)
{
	int i,j;
	int nr_poz=1; // variabila pentru pozitionarea cursorului pe aceasta pozitie si stergerea elementului de dinainte
	int nr_col=1;  // variabila pentru numarul de caractere de la inceputul liniei pana la pozitia la care trebuie sa ajungem
	int nr_lin = 1; // variabila pentru numarul de linii pe care il parcurgem
	char *arg1 = strtok(NULL," "); // luam cele doua argumente
	char *arg2 = strtok(NULL," ");
	Nod *current = *lista_fisier;
	while(current != NULL) // parcurgem lista pentru a ajunge pe linia unde e cursorul, numarand pozitiile
	{
		if(nr_lin == *poz_lin)
			break;
		if(current -> letter == '\n')
			nr_lin++;
		current = current -> next;
		nr_poz++;
	}
	while(nr_col < *poz_col) // parcurgem lista pentru a ajunge pe coloana unde e cursorul, numarud pozitiile
	{
		current = current -> next;
		nr_col++;
		nr_poz++;
	}
	while(current != NULL)
	{
		i = 0;
		while(i < strlen(arg1) && current->letter == arg1[i] ) // parcurgem lista si comparam caracterele
		{
			current = current -> next;
			i++;
		}
		if(i == strlen(arg1)) // in cazul in care gasim cuvantul, il inlocuim
		{
			for(j=0;j<i;j++)
				current = current -> prev;
			for(j=0;j<i;j++)
			{
				current -> letter = arg2[j];
				current = current -> next;
			}
			break;
		}
		else // altfel ne intoarcem la starea initiala cu o pozitie in plus si continuam cautarea
		{
			for(j=0;j<i;j++)
				current = current -> prev;
		}
		current = current -> next;
	}
}

// functie pentru stergerea listei
void deleteListaFisier(Nod **lista_fisier)
{
	int i;
	int size = SizeOf(*lista_fisier);
	for(i=0;i<size;i++)
		deleteNodePos(lista_fisier,1);
}

// functie pentru stergerea listei de istoric/redo
void deleteUndo(list **lista)
{
	int i;
	int lenght = 0;
	list *temp = *lista;
	while ( temp != NULL)
	{
		temp = temp -> next;
		lenght++;
	}
	int lenght2;
	temp = *lista;
	for(i=0;i<lenght;i++)
	{
		lenght2 = SizeOf(temp -> pas);
		for(i=0;i<lenght2;i++)
			deleteNodePos(&(temp)->pas,1);
		temp = temp -> next;
	}
}