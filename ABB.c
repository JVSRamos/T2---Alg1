#include <stdio.h>
#include <stdlib.h>
#include "ABB.h"

void cria_ABB(ABB *a) {
    a->raiz = NULL; // cria uma arvore vazia
    return;
}

void destroiSub(No_ABB *p) {
    if (p == NULL)
        return;
    destroiSub(p->esq); // destroi subarvore esquerda
    destroiSub(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}

void destroi_ABB(ABB *a) {
    destroiSub(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

int vazia(ABB a) {
    return a.raiz == NULL;
}


int buscaSub(No_ABB *p, int x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
    return (x < p->info) ? buscaSub(p->esq, x) : buscaSub(p->dir, x);
}

int busca_ABB(ABB a, int x) {
    return buscaSub(a.raiz, x); // inicia recursao
}

No_ABB *criaNo_ABB(int info, No_ABB *esq, No_ABB *dir) {
    No_ABB *no_ABBva = malloc(sizeof(No_ABB));
    if (no_ABBva != NULL) {
        no_ABBva->info = info;
        no_ABBva->esq = esq;
        no_ABBva->dir = dir;
    }
    return no_ABBva;
}

int insercaoSub(No_ABB **p, int x) {
    // p => No_ABB **; *p => No_ABB *; **p => No_ABB
    if (*p == NULL) {
        *p = criaNo_ABB(x, NULL, NULL); // insere
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    return (x < (*p)->info) ? insercaoSub(&((*p)->esq), x) : insercaoSub(&((*p)->dir), x);
}

int insere_ABB(ABB *a, int x) {
    return insercaoSub(&(a->raiz), x); // inicia recursao
}

int remocaoSub(No_ABB **p, int x) {
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
                return (paiAux->esq == aux) ? remocaoSub(&(paiAux->esq),aux->info) : remocaoSub(&(paiAux->dir),aux->info); // apaga aux e atualiza encadeamento
        }
    }
    return (x < (*p)->info) ? remocaoSub(&((*p)->esq), x) : remocaoSub(&((*p)->dir), x);
}

int remove_ABB(ABB *a, int x) {
    return remocaoSub(&(a->raiz), x); // inicia recursao
}
