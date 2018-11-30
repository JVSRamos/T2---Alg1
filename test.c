#include <stdio.h>

#include "LFREQ.h"

int main() {
	
	LFREQ l;
	cria_LFREQ(&l);

	insere_LFREQ(&l,2);
	insere_LFREQ(&l,4);
	insere_LFREQ(&l,6);
	insere_LFREQ(&l,8);
	insere_LFREQ(&l,9);

	imprime(l);

	busca_LFREQ(&l, 4);
	imprime(l);
	busca_LFREQ(&l, 9);
	imprime(l);

	apaga_LFREQ(&l);


}