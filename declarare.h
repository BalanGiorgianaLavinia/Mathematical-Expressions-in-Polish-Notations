/*BALAN Giorgiana-Lavinia - 311 CB*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 100
#define DELIMS " \n"

//structura pentru arbore
typedef struct arb
{
	void *info;
	struct arb *st, *dr;
}TNod, *TArb, **AArb;

//structura pentru asignari
typedef struct
{
	char nume_var[15];
	int val_numerica;
}TAsign, *TVec;


//declarare functii
TArb BuildNod(void *info);
TArb BuildArb(char *linie);
void RezolvaExpr(char *linie, FILE *out, TAsign *vector, int nrvar);
int TypeOp(char *elem);
int Calculeaza(int term1, int term2, int cod_op, int *valid);
int Valoare(char *var, TAsign *vector, int nrvar, int *valid, FILE *out);
int Evalueaza(TArb arb, FILE *out, TAsign *vector, int nrvar, int *valid);
void DistrugeArb(AArb arb);


