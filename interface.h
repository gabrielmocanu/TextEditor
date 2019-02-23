#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// lista dublu inlantuita ce retine intr-un nod un caracter din stdin
typedef struct Node{
	char letter;
	struct Node *next;
	struct Node *prev;
}Nod; 

// lista in care retin pozitia cursorului dupa o operatie si starea fisierului memorata intr-o lista de tipul de mai sus
typedef struct List{
	Nod *pas;
	int lin;
	int col;
	struct List *next;
	struct List *prev;
}list;


void deleteUndo(list **lista);
void AddNodLast(char letter, Nod **head);
void Addlist(list **head, Nod *aici,int line,int column);
int SizeOf(Nod *head);
void print(Nod *head);
void printList(list *head);
void deleteNodeList(list **head,int poz);
void deleteNodePos( Nod** cap, int n);
void AddNodePos(int position,char letter,Nod **head);
void AddlistAtPosition(int position, list **head, Nod *aici,int line, int column);
void deleteList(Nod** cap);
void INSERT(char *line_read,int *poz_lin,int *poz_col,Nod **lista_fisier,int *nr_operation_aux);
void not_save(int *nr_operation, int *nr_operation_aux, int *nr_operation_for_save);
void go_to_line(int *poz_lin,int *poz_col);
void go_to_char(int *poz_lin,int *poz_col);
void backspace(Nod **lista_fisier,int *poz_lin,int *poz_col);
void delete_line(Nod **lista_fisier,int *poz_lin,int *poz_col);
void delete_char(Nod **lista_fisier,int *poz_lin,int *poz_col);
void save(FILE *fid, Nod **lista_fisier,int *nr_operation_for_save);
void undo(Nod **lista_fisier,list **istoric,list **redo,int *nr_of_undos,int *nr_operation,int *poz_lin,int *poz_col);
void redo_operation(Nod **lista_fisier,list **istoric,list **redo,int *nr_of_redos,int *poz_lin,int *poz_col);
void replace(Nod **lista_fisier,int *poz_lin,int *poz_col);
void deleteListaFisier(Nod **lista_fisier);