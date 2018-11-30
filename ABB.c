#include <stdio.h>
#include <stdlib.h>
#include "ABB.h"

void cria_ABB(ABB *a) {
    a->raiz = NULL; // cria uma arvore vazia
    return;
}

void destroiSub_ABB(No_ABB *p) {
    if (p == NULL)
        return;
    destroiSub_ABB(p->esq); // destroi subarvore esquerda
    destroiSub_ABB(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}

void destroi_ABB(ABB *a) {
    destroiSub_ABB(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

int estavazia_ABB(ABB a) {
    return a.raiz == NULL;
}


int buscaSub_ABB(No_ABB *p, int x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
    return (x < p->info) ? buscaSub_ABB(p->esq, x) : buscaSub_ABB(p->dir, x);
}

int busca_ABB(ABB a, int x) {
    return buscaSub_ABB(a.raiz, x); // inicia recursao
}

No_ABB *criaNo_ABB(int info, No_ABB *esq, No_ABB *dir) {
    No_ABB *nova = malloc(sizeof(No_ABB));
    if (nova != NULL) {
        nova->info = info;
        nova->esq = esq;
        nova->dir = dir;
    }
    return nova;
}

int insercaoSub_ABB(No_ABB **p, int x) {
    // p => No_ABB **; *p => No_ABB *; **p => No_ABB
    if (*p == NULL) {
        *p = criaNo_ABB(x, NULL, NULL); // insere
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    return (x < (*p)->info) ? insercaoSub_ABB(&((*p)->esq), x) : insercaoSub_ABB(&((*p)->dir), x);
}

int insere_ABB(ABB *a, int x) {
    return insercaoSub_ABB(&(a->raiz), x); // inicia recursao
}

int remocaoSub_ABB(No_ABB **p, int x) {
    // p => No_ABB **; *p => No_ABB *; **p => No_ABB
    int numFilhos = 0;
    No_ABB *aux, *paiAux;
    if (*p == NULL)
        return 1; // erro, intento nao existe
    if ((*p)->info == x) { // achou, entao remove
        if ((*p)->esq != NULL)
            numFilhos++;
        if ((*p)->dir != NULL)
            numFilhos++;
        switch (numFilhos) {
            case 0: // nenhum filho
                free(*p); // apaga
                *p = NULL; // atualiza encadeamento
                return 0;
            case 1: // um filho
                aux = *p;
                *p = ((*p)->esq != NULL) ? (*p)->esq : (*p)->dir; // atualiza encadeamento
                free(aux);
                return 0;
            case 2: // dois filhos
                // acha maior filho na subarvore esquerda (aux)
                aux = (*p)->esq;
                paiAux = *p;
                while (aux->dir != NULL) {
                    paiAux = aux;
                    aux = aux->dir;
                }
                (*p)->info = aux->info; // copia info
                return (paiAux->esq == aux) ? remocaoSub_ABB(&(paiAux->esq),aux->info) : remocaoSub_ABB(&(paiAux->dir),aux->info); // apaga aux e atualiza encadeamento
        }
    }
    return (x < (*p)->info) ? remocaoSub_ABB(&((*p)->esq), x) : remocaoSub_ABB(&((*p)->dir), x);
}

int remove_ABB(ABB *a, int x) {
    return remocaoSub_ABB(&(a->raiz), x); // inicia recursao
}
