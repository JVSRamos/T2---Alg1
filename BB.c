#include "BB.h"

void cria_BB(BB *b) {
	b->tam_atual = -1;
}


void shift_vet_insert(BB* b,int pos) {

	int aux,aux2;

	aux = b->v[pos];

	for (int i = pos; i < b->tam_atual + 1; ++i) {
		aux2 = b->v[i+1];
		b->v[i+1] = aux;
		aux = aux2;
	}


}

void shift_vet(BB *b,int pos) {


	for (int i = pos; i < b->tam_atual; ++i) {
		b->v[i] = b->v[i+1];
	}

	b->tam_atual--;
}

int is_full(BB *b) {
	return (b->tam_atual == tam-1);
}

int intern_search(BB *b, int x) {

	for (int i = 0; i < b->tam_atual; ++i) {
		if (b->v[i] == x) return i;
	}

	return -1;

}

int busca_BB(BB *b, int chave, int ini, int fim) {

	
	if (ini > fim) return -1;

	
	int centro = (int)((ini+fim)/2.0);
	if (b->v[centro] == chave)
		return centro;

	if (chave < b->v[centro])
		return busca_BB(b, chave, ini, centro-1);

	if (chave > b->v[centro])
		return busca_BB(b, chave, centro+1, fim);
	
}


int intern_comp(BB *b, int x) {

	for (int i = 0; i < b->tam_atual; ++i) {
		if (b->v[i] > x) return i;
	}

	return -1;

}

void insere_BB(BB *b, int x) {

	if(!is_full(b)) {
		b->tam_atual++;
		int pos = intern_comp(b,x);

		if (pos != -1) {
			shift_vet_insert(b,pos);
			b->v[pos] = x;
		}
		else {
			b->v[b->tam_atual] = x;
		}

	}
}

void remove_BB(BB *b, int x) {

	int pos = busca_BB(b,x,0,b->tam_atual);
	if (pos != -1) {
		shift_vet(b,pos);
	}
}

int estavazia_BB(BB *b) {
	return (b->tam_atual == 0);
}

void destroi_BB(BB *b) {
	b->tam_atual = 0;
}

