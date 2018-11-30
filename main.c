#include <stdio.h>

#include "BB.h"
//#include "LO.h"
//#include "LOS.h"
//#include "ABB.h"

/*
	TODO:
		Resolver conflitos
		AVL - tidia
		AVL remocao
		LFREQ
		BB - falta sort
		LO(feito) - tidia
		LOS(feito) - tidia
		ABB(feito) - tidia

*/

int main() {
	
	Vet v;
	cria_BB(&v);
	insere_BB(&v,1);
	insere_BB(&v,2);
	insere_BB(&v,3);
	insere_BB(&v,4);
	insere_BB(&v,5);

	for(int i = 0; i <= v.tam_atual;i++) {
		printf("%d ", v.v[i]);
	}
	printf("\n");


	int key = busca_binaria(&v,5,0,v.tam_atual);

	printf("%d\n", key);

	retira_BB(&v,4);

	for(int i = 0; i <= v.tam_atual;i++) {
		printf("%d ", v.v[i]);
	}
	printf("\n");

	retira_BB(&v,5);

	for(int i = 0; i <= v.tam_atual;i++) {
		printf("%d ", v.v[i]);
	}
	printf("\n");



	return 0;
}