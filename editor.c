#include "interface.h"
#include "functions.h"

int main(int argc, char const *argv[])
{
	int ok = 0; // variabila ce retine in ce mod suntem, insert sau comanda
	int poz_lin = 1; // pozitia pe linie a cursorului
	int poz_col = 1; // pozitia pe coloana a cursorului
	int nr_operation = 0; // numarul de operatii efectuat
	int nr_operation_for_save = 0 ; // numarul de operatii efectuat ce se contorizeaza pentru a salva fisierul dupa 5 operatii diferite
	int nr_of_undos = 0; // numarul de undo-uri care este facut
	char *operation; // comanda
	int nr_of_redos = 0; // numarul de redo-uri care este facut
	int nr_operation_aux = 0; // variabila pentru a numerota si operatiile facute in modul insert
	Nod *lista_fisier = NULL; // lista pentru retinerea datelor din fisier
	list *istoric = NULL; // lista pentru retinerea istoricului
	list *redo = NULL; // lista care retine operatiile pentru redo
	char *line_read = (char *)malloc(2000*sizeof(char)); // linia pe care o citim
	FILE *fid;

	while(1)
	{
		fgets(line_read,2000,stdin);
		if(!strcmp(line_read,"::i\n")) // Daca se introduce "::i" se schimba modurile, iar daca se trece din modul insert in modul comanda
		{                              // retinem intr-o lista de liste starea curenta pentru a putea efectua undo/redo.
			ok++;
			if(ok%2 == 1)
				Addlist(&istoric,lista_fisier,poz_lin,poz_col);
			continue;
		}
		if(ok%2 == 0)
		{
			INSERT(line_read,&poz_lin,&poz_col,&lista_fisier,&nr_operation_aux); // modul de inserare
		}
		else  // modul de comanda
		{
			operation=strtok(line_read," "); // ne extragem operatia
			if(!strcmp(operation,"q\n")) // quit
			{
				break;
			}	
			if(strcmp(operation,"s\n")) // save
			{
				not_save(&nr_operation,&nr_operation_aux,&nr_operation_for_save);
	 		}
			if(!strcmp(operation,"gl")) // go to line
			{
				go_to_line(&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"gc")) // go to char
			{
				go_to_char(&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"b\n")) // backspace
			{
				backspace(&lista_fisier,&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"dl") || !strcmp(operation,"dl\n")) // delete linie
			{
				delete_line(&lista_fisier,&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"d") || !strcmp(operation,"d\n")) // delete char
			{
				delete_char(&lista_fisier,&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"s\n") || nr_operation_for_save >= 5) //save
			{
				fid = fopen(argv[1],"w+");
				save(fid,&lista_fisier,&nr_operation_for_save);	
			}
			if(!strcmp(operation,"u\n")) //undo
			{
				undo(&lista_fisier,&istoric,&redo,&nr_of_undos,&nr_operation,&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"r\n")) //redo 
			{
				redo_operation(&lista_fisier,&istoric,&redo,&nr_of_redos,&poz_lin,&poz_col);
			}
			if(!strcmp(operation,"re")) //replace
			{
				replace(&lista_fisier,&poz_lin,&poz_col);
			}
			if(strcmp(operation,"s\n") && strcmp(operation,"u\n") && strcmp(operation,"r\n")) // not save,undo,redo
			{
				Addlist(&istoric,lista_fisier,poz_lin,poz_col);
			}
		}
	}
	
	// ELIBERAREA DE MEMORIE
	deleteListaFisier(&lista_fisier);
	free(line_read);
	deleteUndo(&istoric);
	return 0;
}