#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

void cria_AVL(AVL *a) {
    a->raiz = NULL; // cria uma arvore vazia
    return;
}

void destroiSub(No_AVL *p) {
    if (p == NULL)
        return;
    destroiSub(p->esq); // destroi subarvore esquerda
    destroiSub(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}

void destroi_AVL(AVL *a) {
    destroiSub(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

int estavazia_AVL(AVL a) {
    return a.raiz == NULL;
}

void imprimeSub(No_AVL *p) {
    printf("{");
    if (p != NULL) {
        printf("%d:%d, ", p->info, p->fb);
        imprimeSub(p->esq);
        printf(", ");
        imprimeSub(p->dir);
    }
    printf("}");
    return;
}

void imprime(AVL a) {
    imprimeSub(a.raiz);
    printf("\n");
    return;
}

void emOrdemSub(No_AVL *p) {
    if (p != NULL) {
        emOrdemSub(p->esq); // varre lado esquerdo
        printf("%d ", p->info); // processa entre uma subarvore e a outra
        emOrdemSub(p->dir); // varre lado direito
    }
    return;
}

void emOrdem_AVL(AVL a) {
    emOrdemSub(a.raiz); // inicia recursao
    printf("\n");
    return;
}

int buscaSub(No_AVL *p, elem x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
    return (x < p->info) ? buscaSub(p->esq, x) : buscaSub(p->dir, x);
}

int busca(AVL a, elem x) {
    return buscaSub(a.raiz, x); // inicia recursao
}


// rotacao simples a esquerda
void E(No_AVL **p) {
    // p => No_AVL **; *p => No_AVL *; **p => No_AVL
    No_AVL *novoRaiz, *realocar;
    novoRaiz = (*p)->dir;
    realocar = novoRaiz->esq;
    novoRaiz->esq = *p;
    (*p)->dir = realocar;
    *p = novoRaiz;
    return;
}

// rotacao simples a direita
void D(No_AVL **p) {
    // p => No_AVL **; *p => No_AVL *; **p => No_AVL
    No_AVL *novoRaiz, *realocar;
    novoRaiz = (*p)->esq;
    realocar = novoRaiz->dir;
    novoRaiz->dir = *p;
    (*p)->esq = realocar;
    *p = novoRaiz;
    return;
}

void ED(No_AVL **p) {
    E(&((*p)->esq));
    D(p);
    return;
}

void DE(No_AVL **p) {
    D(&((*p)->dir));
    E(p);
    return;
}

No_AVL *criaNo(elem info, No_AVL *esq, No_AVL *dir, int fb) {
    No_AVL *nova = malloc(sizeof(No_AVL));
    if (nova != NULL) {
        nova->info = info;
        nova->esq = esq;
        nova->dir = dir;
        nova->fb = fb;
    }
    return nova;
}

// atualiza fatores de balanceamento apos a rotacao dupla
void atualizaFB(No_AVL *p) {
    switch (p->fb) {
        case 1:
            p->dir->fb = 0;
            p->esq->fb = -1;
            break;
        case -1:
            p->dir->fb = 1;
            p->esq->fb = 0;
            break;
        case 0:
            p->dir->fb = 0;
            p->esq->fb = 0;
            break;
    }
    p->fb = 0;
}

int insercaoSub(No_AVL **p, elem x, int *cresceu) {
    // p => No_AVL **; *p => No_AVL *; **p => No_AVL
    int retorno;
    if (*p == NULL) {
        *p = criaNo(x, NULL, NULL, 0); // insere
        *cresceu = 1; // subarvore cresceu; era nula e agora tem o raiz
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    retorno = insercaoSub((x < (*p)->info) ? &((*p)->esq) : &((*p)->dir), x, cresceu);
    if (!retorno && *cresceu) { // atualiza fator de balanceamento e rebalanceia se necessario
        (*p)->fb += (x < (*p)->info) ? -1 : 1; // atualiza fator de balanceamento
        if ((*p)->fb == 0 || (*p)->fb == 2 || (*p)->fb == -2) {
            *cresceu = 0; // arvore parou de crescer: 0 => melhorou o balanceamento; 2 ou -2 => sera feito o rebalanceamento
            switch ((*p)->fb) {
                case 2: // arvore muito alta a direita
                    if ((*p)->dir->fb == 1) { // mesmo sinal
                        E(p); // rotacao simples a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->esq->fb = 0;
                    } else { // sinais opostos
                        DE(p); // rotacao dupla direita-esquerda
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore muito alta a esquerda
                    if ((*p)->esq->fb == -1) { // mesmo sinal
                        D(p); // rotacao simples a direita
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->dir->fb = 0;
                    } else { // sinais opostos
                        ED(p); // rotacao dupla esquerda-direita
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
    }
    return retorno;
}

int insere_AVL(AVL *a, elem x) {
    int cresceu;
    return insercaoSub(&(a->raiz), x, &cresceu); // inicia recursao
}



int remove_AVL(AVL *a, elem x) {
	int encolheu;
	return remocaoSub(&(a->raiz), x, &encolheu);
}

int remocaoSub(No_AVL **p, elem x, int *encolheu) {
	
	int num_filhos = 0;
	int retorno;
	No_AVL *aux, *paiAux;
	
	if (*p == NULL) return 1;
	if ((*p)->info == x) {
		*encolheu = 1;
		if ((*p)->esq != NULL) num_filhos++; 
		if ((*p)->dir != NULL) num_filhos++;
		
		switch (num_filhos) {
			case 0 :
				free(*p); // apaga
                *p = NULL; // atualiza encadeamento
                return 0;
			case 1 :
				aux = *p;
                *p = ((*p)->esq != NULL) ? (*p)->esq : (*p)->dir; // atualiza encadeamento
                free(aux);
                return 0;
			case 2 :
				aux = (*p)->esq;
                paiAux = *p;
                while (aux->dir != NULL) {
                    paiAux = aux;
                    aux = aux->dir;
                }
                (*p)->info = aux->info; // copia info
                return (paiAux->esq == aux) ? remocaoSub(&(paiAux->esq),aux->info,encolheu) : remocaoSub(&(paiAux->dir),aux->info,encolheu);		
		}
		
	}
	
	retorno = (x > (*p)->info) ? remocaoSub((&(*p)->dir),x,encolheu) : remocaoSub((&(*p)->esq),x,encolheu); 
	
	if (!retorno && encolheu) {
		(*p)->fb += (x < (*p)->info) ? -1 : 1; // atualiza fator de balanceamento
        if ((*p)->fb == 0 || (*p)->fb == 2 || (*p)->fb == -2) {
            *encolheu = 0; // arvore parou de crescer: 0 => melhorou o balanceamento; 2 ou -2 => sera feito o rebalanceamento
            switch ((*p)->fb) {
                case 2: // arvore muito alta a direita
                    if ((*p)->dir->fb == 1) { // mesmo sinal
                        E(p); // rotacao simples a esquerda
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->esq->fb = 0;
                    } else { // sinais opostos
                        DE(p); // rotacao dupla direita-esquerda
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
                case -2: // arvore muito alta a esquerda
                    if ((*p)->esq->fb == -1) { // mesmo sinal
                        D(p); // rotacao simples a direita
                        // atualiza fatores de balanceamento
                        (*p)->fb = 0;
                        (*p)->dir->fb = 0;
                    } else { // sinais opostos
                        ED(p); // rotacao dupla esquerda-direita
                        atualizaFB(*p); // atualiza fatores de balanceamento
                    }
                    break;
            }
        }
	}
	
	
	

}
















