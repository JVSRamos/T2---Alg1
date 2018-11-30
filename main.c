#include <stdio.h>	/* printf */
#include <stdlib.h>	/* rand */
#include <time.h>	/* clock_t, clock, CLOCKS_PER_SEC */
#include "BB.h"
#include "LO.h"
#include "LOS.h"
#include "ABB.h"
#include "AVL.h"
//#include "LFREQ.h"

/*
	TODO:
		AVL remocao
		LFREQ
		BB - falta sort
	
*/

int main(void) {
	
	srand(time(NULL));	//deixa a seed para a geracao dos numeros do rand mais "aleatoria"
	
	BB estr1;	//estrutura 1
	ListaOrd estr2;	//estrutura 2
	ListaOrds estr3;	//estrutura 3
	ABB estr4;	//estrutura 4
	AVL estr5;	//estrutura 5
	//LFREQ estr6;	//estrutura 6
	clock_t tent;
	int n[4];
	double tempo[6][4];
	double media;
	
	cria_BB(&estr1);
	cria_LO(&estr2);
	cria_LOS(&estr3);
	cria_ABB(&estr4);
	cria_AVL(&estr5);
	//cria_LFREQ(&estr6);
	n[0] = 100;
	n[1] = 1000;
	n[2] = 10000;
	n[3] = 100000;
	
	for (int ni = 0; ni < 4; i++) {		//vai coletar os dados da BB
		media = 0;
		for (int i = 0; i < 10; i++) {
			
		
		}
		
		media = media/10;
		tempo[0][ni] = media;
	}
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
				
			
		
		
		
		
		}
	}	
	
	
	destroi_BB(&estr1);
	destroi_LO(&estr2);
	destroi_LOS(&estr3);
	destroi_ABB(&estr4);
	destroi_AVL(&estr5);
	//destroi_LFREQ(&estr6);

	return 0;
}
