#include <stdlib.h>
#include <stdio.h>
#include "LOS.h"

int cria_LOS(ListaOrds *l) {
    l->sentinela = malloc(sizeof(No_LOS));
    if (l->sentinela == NULL)
        return 1; // erro
    l->sentinela->prox = NULL;
    l->ini = l->sentinela;
    return 0; // sucesso
}

void destroi_LOS(ListaOrds *l) {
    No_LOS *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    l->sentinela = NULL;
    return;
}

void busca_interna(ListaOrds *l, int x, No_LOS **ant, No_LOS **p) {
    // ant, p => No_LOS **
    // *ant, *p => No_LOS *
    // **ant, **p => No_LOS
    l->sentinela->info = x;
    *ant = NULL;
    *p = l->ini;
    while ((*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

int insere_LOS(ListaOrds *l, int x) {
    No_LOS *no_LOSvo, *ant, *p;
    busca_interna(l, x, &ant, &p); // busca primeiro maior ou igual a x
    if (p != l->sentinela && p->info == x)
        return 1; // erro, intento repetido
    no_LOSvo = (No_LOS *) malloc(sizeof(No_LOS));
    if (no_LOSvo == NULL)
        return 1; // erro, memoria insuficiente
    no_LOSvo->info = x; // copia informacao
    // atualiza ponteiros
    no_LOSvo->prox = p;
    if (ant == NULL)
        l->ini = no_LOSvo; // insere no_LOS inicio
    else
        ant->prox = no_LOSvo; // insere no_LOS meio ou fim
    return 0; // sucesso
}

int remove_LOS(ListaOrds *l, int x) {
    No_LOS *ant, *p;
    busca_interna(l, x, &ant, &p);
    if (p == l->sentinela || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

int busca_LOS(ListaOrds l, int x) {
    l.sentinela->info = x;
    while(l.ini->info < x)
        l.ini = l.ini->prox;
    return (l.ini != l.sentinela && l.ini->info == x);
}

int estavazia_LOS(ListaOrds l) {
    return (l.ini == l.sentinela);
}
