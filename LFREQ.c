#include <stdio.h>
#include <stdlib.h>

#include "LFREQ.h"

void cria_LFREQ(LFREQ *l) {
    l->ini = NULL;
    l->fim = NULL;
    return;
}

void destroi_LFREQ(LFREQ *l) {
    No_LFREQ *p;
    p = l->ini;
    do {
        if (p != NULL) p = p->prox;
        free(p);
    } while (p != l->ini);
    return;
}

int insere_LFREQ(LFREQ *l, int x) {

    No_LFREQ *p = malloc(sizeof(No_LFREQ));
    p->info = x;
    p->ant = NULL;
    p->prox = NULL;

    if (l->ini == NULL) {
        l->ini = p;
    }
    else {
        l->fim->prox = p;
        p->ant = l->fim;
    }

    l->fim = p;
    l->fim->prox = l->ini;
    l->ini->ant = l->fim;

}

void buscainterna_LFREQ(LFREQ *l, int x, No_LFREQ **p) {
    *p = l->ini;
    // contador para marcar se ja passou uma vez a lista
    int count = 0;
    
    do {
        *p = (*p)->prox;
        count++;
    } while (*p != l->ini && (*p)->info != x);

	//caso em que nao acha o elemento
	if (count > 1 && *p == l->ini)  *p = NULL;
		return;
}

int busca_LFREQ(LFREQ *l, int x) {

    No_LFREQ *p;
    buscainterna_LFREQ(l, x, &p);


    if (p != NULL && p != l->ini) {
     
		int aux = p->info;
		p->info = p->ant->info;
		p->ant->info = aux;
		
        return 1;
    }

	if (p != NULL && p == l->ini) return 1;

    return 0;
}


void remove_LFREQ(LFREQ *l, int x) {

    No_LFREQ* p;
    buscainterna_LFREQ(l,x,&p);

    if (p != NULL) {
        if (p == l->ini) {
            l->ini = p->prox;
            l->ini->ant = l->fim;
            l->fim->prox = l->ini;
        }
        else if (p == l->fim) {
            l->fim = p->ant;
            l->fim->prox = l->ini;
            l->ini->ant = l->fim;   
        }
        else {
            p->ant->prox = p->prox;
            p->prox->ant = p->ant;
           
        }
     free(p);

    }
}



