/*BALAN Giorgiana-Lavinia - 311 CB*/

#include "declarare.h"


//functie care construieste nod cu informatia info
TArb BuildNod(void *info)
{
	TArb nod = NULL;

	//aloc dinamic structura pentru nod
	nod = (TArb)calloc(sizeof(TNod), 1);
	if(!nod)
		return NULL;

	nod->info = info;
	nod->st = NULL;
	nod->dr = NULL;

	return nod;
}


//functie care determina tipul operatorului
int TypeOp(char *elem)
{
	if(strcmp(elem, "+") == 0)
		return 1;
	else
	{
		if(strcmp(elem, "-") == 0)
			return 2;
		else
		{
			if(strcmp(elem, "*") == 0)
				return 3;
			else
			{
				if(strcmp(elem, "/") == 0)
					return 4;
				else
				{
					if(strcmp(elem, "^") == 0)
						return 5;
					else
					{
						if(strcmp(elem, "sqrt") == 0)
							return 6;
					}
				}
			}

		}

	}

	//daca nu e niciunul din operatori functia intoarce 0
	return 0;
}



//functie care construieste arborele
TArb BuildArb(char *linie)
{
	char *token = NULL;
	token = strtok(linie, DELIMS);

	char *elemExpr = (char *)calloc(strlen(token) + 1, 1);
	if(!elemExpr)
		return NULL;
	memcpy(elemExpr, token, strlen(token));

	//bag primul nod in arbore
	TArb arb = NULL;
	arb = BuildNod(elemExpr);
	if(arb == NULL)
	{
		free(elemExpr);
		return NULL;
	}

	//daca este operator
	if(TypeOp(elemExpr) != 0)
	{
		arb->st = BuildArb(NULL);

		//construiesc arborele drept doar daca 
		//parintele nu este sqrt 
		if(TypeOp(elemExpr) != 6)
			arb->dr = BuildArb(NULL);
	}
	return arb;
}


//functie care calculeaza expresia dorita
int Calculeaza(int term1, int term2, int cod_op, int *valid)
{
	if(*valid != 1)
		return 0;

	if(cod_op == 0)
	{
		//daca nu este operator, expresia nu este valida
		*valid = 0;
	}
	else
	{
		if(cod_op == 1)
		{
			return term1 + term2;
		}
		else
		{
			if(cod_op == 2)
			{
				return term1 - term2;
			}
			else
			{
				if(cod_op == 3)
				{
					return term1 * term2;
				}
				else
				{
					if(cod_op == 4)
					{
						if(term2 == 0)
						{
							*valid = 0;
							return -1;
						}

						return term1 / term2;
					}
					else
					{
						if(cod_op == 5)
						{
							return pow(term1, term2);
						}
						else
						{
							if(cod_op == 6)
							{
								if(term1 < 0)
								{
									*valid = 0;
									return -1;
								}
								return sqrt(term1);
							}
						}
					}
				}
			}
		}

	}
	return -1;
}


//functie care intoarce valoarea operandului
int Valoare(char *var, TAsign *vector, int nrvar, int *valid, FILE *out)
{
	if(*valid != 1)
		return 0;

	char cifra = '0';
	memcpy(&cifra, var, sizeof(char));

	//daca primul caracter din sir este minus sau cifra inseamna ca 
	//este numar
	if(cifra == '-' || (cifra >= '0' && cifra <= '9'))
	{
		return atoi(var);
	}
	else
	{
		//caut variabila in vector
		int i = 0;
		for(i = 0; i < nrvar; i++)
		{
			//daca gaseste numele variabilei ii intorc valoarea
			if(strcmp(vector[i].nume_var, var) == 0)
				return vector[i].val_numerica;
		}

		//daca iese din for inseamna ca nu a gasit variabila si
		//scriu in fisier ca variabila nu exista
		*valid = -1;
		fprintf(out, "Variable %s undeclared\n", var);

		return -1;
	}
}


//functie care calculeaza expresiile
int Evalueaza(TArb arb, FILE *out, TAsign *vector, int nrvar, int *valid)
{
	if(*valid != 1)
		return 0;

	int term1 = 0;
	int term2 = 0;

	//calculez expresiile pentru operatorii -, +, *, /, ^ 
	if(TypeOp(arb->info) > 0 && TypeOp(arb->info) < 6)
	{
		term1 = Evalueaza(arb->st, out, vector, nrvar, valid);
		term2 = Evalueaza(arb->dr, out, vector, nrvar, valid);
		return Calculeaza(term1, term2, TypeOp(arb->info), valid);
	}

	//calculez expresiile pentru radical
	if(TypeOp(arb->info) == 6)
	{
		term1 = Evalueaza(arb->st, out, vector, nrvar, valid);
		return Calculeaza(term1, term2, TypeOp(arb->info), valid);
	}

	//nu este operator, deci este o variabila sau un numar,
	//il voi converti la int si il returnez
	return Valoare(arb->info, vector, nrvar, valid, out);
}


//functie care scrie in out rezultatul expresiei si 
//verifica daca e expresie valida
void RezolvaExpr(char *linie, FILE *out, TAsign *vector, int nrvar)
{
	TArb arb = NULL;
	arb = BuildArb(linie);

	//presupun ca expresia este valida
	int valid = 1;

	int calcul = 0;
	calcul = Evalueaza(arb, out, vector, nrvar, &valid);
	
	if(valid == 0)
	{
		fprintf(out, "Invalid expression\n");
	}

	if(valid == 1)
	{
		fprintf(out, "%d\n", calcul);
	}

	DistrugeArb(&arb);
}

void DistrugeArb(AArb arb)
{
	if(*arb == NULL)
		return;

	DistrugeArb(&((*arb)->st));
	DistrugeArb(&((*arb)->dr));

	free((*arb)->info);
	free(*arb);
	*arb = NULL;
}






