/*BALAN Giorgiana-Lavinia - 311 CB*/

#include "declarare.h"

int main(int argc, char const *argv[])
{
	if(argc != 3)
		return -1;

	FILE *in = NULL;
	FILE *out = NULL;

	//deschid fisierele
	in = fopen(argv[1], "rt");
	out = fopen(argv[2], "wt");

	//citesc din in prima linie
	char *linie = NULL;
	size_t lungime = MAX;
	getline(&linie, &lungime, in);

	//aflu numarul de variabile
	char *token = NULL;
	token = strtok(linie, DELIMS);
	int nrvar = 0;
	nrvar = atoi(token);

	//retin intr-un vector asignarile
	TAsign vec_asign[50] = {0};
	int i = 0;
	for(i = 0; i < nrvar; i++)
	{
		getline(&linie, &lungime, in);
		token = strtok(linie, DELIMS);
		memcpy(vec_asign[i].nume_var, token, strlen(token));

		//obtin "=" pe care nu il folosesc 
		token = strtok(NULL, DELIMS);

		token = strtok(NULL, DELIMS);
		vec_asign[i].val_numerica = atoi(token);

	}

	//aflu numarul de expresii
	getline(&linie, &lungime, in);
	token = strtok(linie, DELIMS);

	int nrexpr = 0;
	nrexpr = atoi(token);

	int j = 0;
	for(j = 0; j < nrexpr; j++)
	{
		getline(&linie, &lungime, in);
		RezolvaExpr(linie, out, vec_asign, nrvar);
	}

	free(linie);
	
	//inchid fisiere
	fclose(in);
	fclose(out);

	return 0;
}