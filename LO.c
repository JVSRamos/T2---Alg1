#include <stdlib.h>
#include <stdio.h>
#include "LO.h"

void cria_LO(ListaOrd *l) {
    l->ini = NULL;
    return;
}

void buscainterna(ListaOrd *l, int x, No_LO **ant, No_LO **p) {
    // ant, p => No_LO **
    // *ant, *p => No_LO *
    // **ant, **p => No_LO
    *ant = NULL;
    *p = l->ini;
    while (*p != NULL && (*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

int insere_LO(ListaOrd *l, int x) {
    No_LO *novo, *ant, *p;
    buscainterna(l, x, &ant, &p); // busca primeiro maior ou igual a x
    if (p != NULL && p->info == x)
        return 1; // erro, intento repetido
    novo = (No_LO *) malloc(sizeof(No_LO));
    if (novo == NULL)
        return 1; // erro, memoria insuficiente
    novo->info = x; // copia informacao
    // atualiza ponteiros
    novo->prox = p;
    if (ant == NULL)
        l->ini = novo; // insere no_LO inicio
    else
        ant->prox = novo; // insere no_LO meio ou fim
    return 0; // sucesso
}

int remove_LO(ListaOrd *l, int x) {
    No_LO *ant, *p;
    buscainterna(l, x, &ant, &p);
    if (p == NULL || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

int busca_LO(ListaOrd l, int x) {
    while(l.ini != NULL && l.ini->info < x)
        l.ini = l.ini->prox;
    return (l.ini != NULL && l.ini->info == x);
}

int estavazia_LO(ListaOrd l) {
    return (l.ini == NULL);
}

void destroi_LO(ListaOrd *l) {
    No_LO *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    return;
}
