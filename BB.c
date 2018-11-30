#include "BB.h"

void cria_BB(Vet* b) {
	b->tam_atual = -1;
}

int busca_binaria(Vet* b, int chave, int ini, int fim) {

	
	if (ini > fim) return -1;

	
	int centro = (int)((ini+fim)/2.0);
	if (b->v[centro] == chave)
		return centro;

	if (chave < b->v[centro])
		return busca_binaria(b, chave, ini, centro-1);

	if (chave > b->v[centro])
		return busca_binaria(b, chave, centro+1, fim);
	
}

void insere_BB(Vet* b, int x) {
	b->tam_atual++;
	b->v[b->tam_atual] = x;
}

void shift_vet(Vet* b,int pos) {


	for (int i = pos; i < b->tam_atual; ++i) {
		b->v[i] = b->v[i+1];
	}

	b->tam_atual--;
}

int intern_search(Vet *b, int x) {

	for (int i = 0; i < tam; ++i) {
		if (b->v[i] == x) return i;
	}

	return -1;

}

void retira_BB(Vet* b, int x) {

	int pos = intern_search(b,x);
	if (pos != -1) {
		shift_vet(b,pos);
	}
}






