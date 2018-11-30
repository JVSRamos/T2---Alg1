#include <stdio.h>
#include <stdlib.h>

#include "LFREQ.h"

void cria_LFREQ(LFREQ *l) {
    l->ini = NULL;
    l->fim = NULL;
    return;
}

void apaga_LFREQ(LFREQ *l) {
    No_LFREQ *p;
    p = l->ini;
    do {
        l->ini = l->ini->prox;
        free(p);
        p = l->ini;
    } while (l->ini != l->fim);
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
    while (*p != NULL && (*p)->info != x) {
        *p = (*p)->prox;
    }

    return;
}


void swap(No_LFREQ* p, No_LFREQ* ant) {

    No_LFREQ* aux = p->prox;

    p->prox = ant;
    p->ant = ant->ant;
    ant->prox = aux;
    ant->ant = p;
}


int busca_LFREQ(LFREQ *l, int x) {

    No_LFREQ *p;
    buscainterna_LFREQ(l, x, &p);

    if (p != NULL && p != l->ini) {
        //swap(p,p->ant); 

        No_LFREQ* aux = p->prox;

        p->prox = p->ant;
        p->ant = p->ant->ant;
        p->ant->prox = aux;
        p->ant->ant = p;


        return 1;
    }

    if (p != NULL && p == l->ini) return 1;

    return 0;
}

/*
void retira_LFREQ(LFREQ *l, int x) {

    No_LFREQ* pos;
    buscainterna_LFREQ(l,x,pos);

    if (pos != NULL) {
        if (pos == l->ini) {
            pos->prox = l->ini;
            l->ini->ant = l->fim;
            l->fim_>prox = l->ini;
        }
        else if (pos == l->end) {
            pos->ant = l->fim;
            l->fim_>prox = l->ini;
            l->ini->ant = l->fim;   
        }
        else {
            pos->ant = pos->prox;
            

        }

    }



}
*/


void imprime(LFREQ l) {

    No_LFREQ *p = l.ini;

    do { 
        printf("%d\n", p->info);
        p = p->prox;
    }   while (p != l.ini);
    return;
}



