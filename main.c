#include <stdio.h>	/* printf */
#include <stdlib.h>	/* rand, srand */
#include <time.h>	/* time, clock_t, clock */
#include "BB.h"
#include "LO.h"
#include "LOS.h"
#include "ABB.h"
#include "AVL.h"
#include "LFREQ.h"

/*
	TODO: Remover TODOS os "/*" (especialmente no final, onde eu destruo)
*/

int main(void) {
	
	srand(time(NULL));	//deixa a seed para a geracao dos numeros do rand mais "aleatoria"
	
	BB estr1;	//estrutura 1
	ListaOrd estr2;	//estrutura 2
	ListaOrds estr3;	//estrutura 3
	ABB estr4;	//estrutura 4
	AVL estr5;	//estrutura 5
	LFREQ estr6;	//estrutura 6
	int n[4];	//guarda os numeros que vao ser utilizados para os testes
	clock_t tempo;
	int n_ale;
	int count;	//utilizado para as insercoes aleatorias
	int *usado = malloc(100000*sizeof(int));	//vetor para auxiliar nas insercoes aleatorias
	int *numero = malloc(100000*sizeof(int));	//vai ser utilizado para nao modificar o resultado de tempo nas insercoes aleatorias
	double tabela[9][6][4];	//9 tabelas, cada uma com 6 linhas e 4 colunas
	
	cria_BB(&estr1);
	cria_LO(&estr2);
	cria_LOS(&estr3);
	cria_ABB(&estr4);
	cria_AVL(&estr5);
	cria_LFREQ(&estr6);
	n[0] = 100;
	n[1] = 1000;
	n[2] = 10000;
	n[3] = 100000;
	
	for (int i = 0; i < 9; i++) {	//inicializa a tabela com 0s
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				tabela[i][j][k] = 0.0;
			}
		}
	}
	/*
	for (int ni = 0; ni < 4; ni++) {
		//a partir daqui, ja tenho um valor de n fixado
		
		//primeiro, faco a insercao crescente e os testes apropriados para a BB
		
		for (int j = 0; j < 20; j++) {
			
			if (j < 10) {	//as primeiras 10 insercoes irao ajudar na contagem do tempo da busca e da remocao crescente
				//primeiro, faco a insercao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) insere_BB(&estr1, k);
				tempo = clock() - tempo;
				tabela[0][0][ni] += (double)tempo;
				
				//depois, a busca
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) {
					n_ale = rand();
					if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
						n_ale = n_ale % n[ni];
						busca_BB(&estr1, n_ale, 0, n[ni]);
					} else {	//para a outra metade, faco por inexistentes
						n_ale += n[ni];
						busca_BB(&estr1, n_ale, 0, n[ni]);
					}
				}
				tempo = clock() - tempo;
				tabela[6][0][ni] += (double)tempo;
				
				//por ultimo, a remocao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) remove_BB(&estr1, k+n[ni]/2);	//fazendo assim, estou tentando remover tanto numeros existentes quanto numeros inexistentes, numa proporcao de 1:1 (os primeiros k/2 existirao, mas os ultimos k/2 nao)
				tempo = clock() - tempo;
				tabela[3][0][ni] += (double)tempo;
				
			} else {	//as ultimas 10 insercoes irao ajudar apenas na contagem da remocao decrescente
				//insercao
				for (int k = 0; k < n[ni]; k++) insere_BB(&estr1, k);
				//remocao (decrescente)
				tempo = clock();
				for (int k = n[ni]-1; k >= 0; k--) remove_BB(&estr1, k+n[ni]/2);	//os primeiros k/2 numeros serao inexistentes, mas os ultimos k/2 existirao 
				tempo = clock() - tempo;
				tabela[4][0][ni] += (double)tempo;
			}
			
			destroi_BB(&estr1);
			cria_BB(&estr1);	//faco isso para "resetar" a estrutura
		}
		tabela[0][0][ni] /= 10.0;
		tabela[6][0][ni] /= 10.0;
		tabela[3][0][ni] /= 10.0;
		tabela[4][0][ni] /= 10.0;
		
		
		//agora, faco o mesmo procedimento do for anterior, so que para a LO
		
		for (int j = 0; j < 20; j++) {
			
			if (j < 10) {	//as primeiras 10 insercoes irao ajudar na contagem do tempo da busca e da remocao crescente
				//primeiro, faco a insercao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) insere_LO(&estr2, k);
				tempo = clock() - tempo;
				tabela[0][1][ni] += (double)tempo;
				
				//depois, a busca
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) {
					n_ale = rand();
					if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
						n_ale = n_ale % n[ni];
						busca_LO(estr2, n_ale);
					} else {	//para a outra metade, faco por inexistentes
						n_ale += n[ni];
						busca_LO(estr2, n_ale);
					}
				}
				tempo = clock() - tempo;
				tabela[6][1][ni] += (double)tempo;
				
				//por ultimo, a remocao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) remove_LO(&estr2, k+n[ni]/2);	//fazendo assim, estou tentando remover tanto numeros existentes quanto numeros inexistentes, numa proporcao de 1:1 (os primeiros k/2 existirao, mas os ultimos k/2 nao)
				tempo = clock() - tempo;
				tabela[3][1][ni] += (double)tempo;
				
			} else {	//as ultimas 10 insercoes irao ajudar apenas na contagem da remocao decrescente
				//insercao
				for (int k = 0; k < n[ni]; k++) insere_LO(&estr2, k);
				//remocao (decrescente)
				tempo = clock();
				for (int k = n[ni]-1; k >= 0; k--) remove_LO(&estr2, k+n[ni]/2);	//os primeiros k/2 numeros serao inexistentes, mas os ultimos k/2 existirao 
				tempo = clock() - tempo;
				tabela[4][1][ni] += (double)tempo;
			}
			
			destroi_LO(&estr2);
			cria_LO(&estr2);	//faco isso para "resetar" a estrutura
		}
		tabela[0][1][ni] /= 10.0;
		tabela[6][1][ni] /= 10.0;
		tabela[3][1][ni] /= 10.0;
		tabela[4][1][ni] /= 10.0;
		
		//para a LOS
		
		for (int j = 0; j < 20; j++) {
			
			if (j < 10) {	//as primeiras 10 insercoes irao ajudar na contagem do tempo da busca e da remocao crescente
				//primeiro, faco a insercao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) insere_LOS(&estr3, k);
				tempo = clock() - tempo;
				tabela[0][2][ni] += (double)tempo;
				
				//depois, a busca
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) {
					n_ale = rand();
					if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
						n_ale = n_ale % n[ni];
						busca_LOS(estr3, n_ale);
					} else {	//para a outra metade, faco por inexistentes
						n_ale += n[ni];
						busca_LOS(estr3, n_ale);
					}
				}
				tempo = clock() - tempo;
				tabela[6][2][ni] += (double)tempo;
				
				//por ultimo, a remocao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) remove_LOS(&estr3, k+n[ni]/2);	//fazendo assim, estou tentando remover tanto numeros existentes quanto numeros inexistentes, numa proporcao de 1:1 (os primeiros k/2 existirao, mas os ultimos k/2 nao)
				tempo = clock() - tempo;
				tabela[3][2][ni] += (double)tempo;
				
			} else {	//as ultimas 10 insercoes irao ajudar apenas na contagem da remocao decrescente
				//insercao
				for (int k = 0; k < n[ni]; k++) insere_LOS(&estr3, k);
				//remocao (decrescente)
				tempo = clock();
				for (int k = n[ni]-1; k >= 0; k--) remove_LOS(&estr3, k+n[ni]/2);	//os primeiros k/2 numeros serao inexistentes, mas os ultimos k/2 existirao 
				tempo = clock() - tempo;
				tabela[4][2][ni] += (double)tempo;
			}
			
			destroi_LOS(&estr3);
			cria_LOS(&estr3);	//faco isso para "resetar" a estrutura
		}
		tabela[0][2][ni] /= 10.0;
		tabela[6][2][ni] /= 10.0;
		tabela[3][2][ni] /= 10.0;
		tabela[4][2][ni] /= 10.0;
		
		//ABB
		
		for (int j = 0; j < 20; j++) {
			
			if (j < 10) {	//as primeiras 10 insercoes irao ajudar na contagem do tempo da busca e da remocao crescente
				//primeiro, faco a insercao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) insere_ABB(&estr4, k);
				tempo = clock() - tempo;
				tabela[0][3][ni] += (double)tempo;
				
				//depois, a busca
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) {
					n_ale = rand();
					if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
						n_ale = n_ale % n[ni];
						busca_ABB(estr4, n_ale);
					} else {	//para a outra metade, faco por inexistentes
						n_ale += n[ni];
						busca_ABB(estr4, n_ale);
					}
				}
				tempo = clock() - tempo;
				tabela[6][3][ni] += (double)tempo;
				
				//por ultimo, a remocao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) remove_ABB(&estr4, k+n[ni]/2);	//fazendo assim, estou tentando remover tanto numeros existentes quanto numeros inexistentes, numa proporcao de 1:1 (os primeiros k/2 existirao, mas os ultimos k/2 nao)
				tempo = clock() - tempo;
				tabela[3][3][ni] += (double)tempo;
				
			} else {	//as ultimas 10 insercoes irao ajudar apenas na contagem da remocao decrescente
				//insercao
				for (int k = 0; k < n[ni]; k++) insere_ABB(&estr4, k);
				//remocao (decrescente)
				tempo = clock();
				for (int k = n[ni]-1; k >= 0; k--) remove_ABB(&estr4, k+n[ni]/2);	//os primeiros k/2 numeros serao inexistentes, mas os ultimos k/2 existirao 
				tempo = clock() - tempo;
				tabela[4][3][ni] += (double)tempo;
			}
			
			destroi_ABB(&estr4);
			cria_ABB(&estr4);	//faco isso para "resetar" a estrutura
		}
		tabela[0][3][ni] /= 10.0;
		tabela[6][3][ni] /= 10.0;
		tabela[3][3][ni] /= 10.0;
		tabela[4][3][ni] /= 10.0;
		
		//AVL
		
		for (int j = 0; j < 20; j++) {
			
			if (j < 10) {	//as primeiras 10 insercoes irao ajudar na contagem do tempo da busca e da remocao crescente
				//primeiro, faco a insercao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) insere_AVL(&estr5, k);
				tempo = clock() - tempo;
				tabela[0][4][ni] += (double)tempo;
				
				//depois, a busca
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) {
					n_ale = rand();
					if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
						n_ale = n_ale % n[ni];
						busca_AVL(estr5, n_ale);
					} else {	//para a outra metade, faco por inexistentes
						n_ale += n[ni];
						busca_AVL(estr5, n_ale);
					}
				}
				tempo = clock() - tempo;
				tabela[6][4][ni] += (double)tempo;
				
				//por ultimo, a remocao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) remove_AVL(&estr5, k+n[ni]/2);	//fazendo assim, estou tentando remover tanto numeros existentes quanto numeros inexistentes, numa proporcao de 1:1 (os primeiros k/2 existirao, mas os ultimos k/2 nao)
				tempo = clock() - tempo;
				tabela[3][4][ni] += (double)tempo;
				
			} else {	//as ultimas 10 insercoes irao ajudar apenas na contagem da remocao decrescente
				//insercao
				for (int k = 0; k < n[ni]; k++) insere_AVL(&estr5, k);
				//remocao (decrescente)
				tempo = clock();
				for (int k = n[ni]-1; k >= 0; k--) remove_AVL(&estr5, k+n[ni]/2);	//os primeiros k/2 numeros serao inexistentes, mas os ultimos k/2 existirao 
				tempo = clock() - tempo;
				tabela[4][4][ni] += (double)tempo;
			}
			
			destroi_AVL(&estr5);
			cria_AVL(&estr5);	//faco isso para "resetar" a estrutura
		}
		tabela[0][4][ni] /= 10.0;
		tabela[6][4][ni] /= 10.0;
		tabela[3][4][ni] /= 10.0;
		tabela[4][4][ni] /= 10.0;
		
		//e LFREQ
		
		for (int j = 0; j < 20; j++) {
			
			if (j < 10) {	//as primeiras 10 insercoes irao ajudar na contagem do tempo da busca e da remocao crescente
				//primeiro, faco a insercao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) insere_LFREQ(&estr6, k);
				tempo = clock() - tempo;
				tabela[0][5][ni] += (double)tempo;
				
				//depois, a busca
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) {
					n_ale = rand();
					if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
						n_ale = n_ale % n[ni];
						busca_LFREQ(&estr6, n_ale);
					} else {	//para a outra metade, faco por inexistentes
						n_ale += n[ni];
						busca_LFREQ(&estr6, n_ale);
					}
				}
				tempo = clock() - tempo;
				tabela[6][5][ni] += (double)tempo;
				
				//por ultimo, a remocao
				tempo = clock();
				for (int k = 0; k < n[ni]; k++) remove_LFREQ(&estr6, k+n[ni]/2);	//fazendo assim, estou tentando remover tanto numeros existentes quanto numeros inexistentes, numa proporcao de 1:1 (os primeiros k/2 existirao, mas os ultimos k/2 nao)
				tempo = clock() - tempo;
				tabela[3][5][ni] += (double)tempo;
				
			} else {	//as ultimas 10 insercoes irao ajudar apenas na contagem da remocao decrescente
				//insercao
				for (int k = 0; k < n[ni]; k++) insere_LFREQ(&estr6, k);
				//remocao (decrescente)
				tempo = clock();
				for (int k = n[ni]-1; k >= 0; k--) remove_LFREQ(&estr6, k+n[ni]/2);	//os primeiros k/2 numeros serao inexistentes, mas os ultimos k/2 existirao 
				tempo = clock() - tempo;
				tabela[4][5][ni] += (double)tempo;
			}
			
			destroi_LFREQ(&estr6);
			cria_LFREQ(&estr6);	//faco isso para "resetar" a estrutura
		}
		tabela[0][5][ni] /= 10.0;
		tabela[6][5][ni] /= 10.0;
		tabela[3][5][ni] /= 10.0;
		tabela[4][5][ni] /= 10.0;
		
		
		//agora, faco a insercao decrescente e os testes apropriados, comecando pela BB
		
		for (int j = 0; j < 10; j++) {
			//primeiro, faco a insercao
			tempo = clock();
			for (int k = n[ni]-1; k >= 0; k--) insere_BB(&estr1, k);
			tempo = clock() - tempo;
			tabela[1][0][ni] += tempo;
			
			//agora, faco a busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_BB(&estr1, n_ale, 0, n[ni]);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_BB(&estr1, n_ale, 0, n[ni]);
				}
			}
			tempo = clock() - tempo;
			tabela[7][0][ni] += tempo;
			
			destroi_BB(&estr1);
			cria_BB(&estr1);	//faco isso para "resetar" a estrutura
		}
		tabela[1][0][ni] /= 10.0;
		tabela[7][0][ni] /= 10.0;
		
		//LO
		
		for (int j = 0; j < 10; j++) {
			//primeiro, faco a insercao
			tempo = clock();
			for (int k = n[ni]-1; k >= 0; k--) insere_LO(&estr2, k);
			tempo = clock() - tempo;
			tabela[1][1][ni] += tempo;
			
			//agora, faco a busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_LO(estr2, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_LO(estr2, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[7][1][ni] += tempo;
			
			destroi_LO(&estr2);
			cria_LO(&estr2);	//faco isso para "resetar" a estrutura
		}
		tabela[1][1][ni] /= 10.0;
		tabela[7][1][ni] /= 10.0;
		
		//LOS
		
		for (int j = 0; j < 10; j++) {
			//primeiro, faco a insercao
			tempo = clock();
			for (int k = n[ni]-1; k >= 0; k--) insere_LOS(&estr3, k);
			tempo = clock() - tempo;
			tabela[1][2][ni] += tempo;
			
			//agora, faco a busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_LOS(estr3, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_LOS(estr3, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[7][2][ni] += tempo;
			
			destroi_LOS(&estr3);
			cria_LOS(&estr3);	//faco isso para "resetar" a estrutura
		}
		tabela[1][2][ni] /= 10.0;
		tabela[7][2][ni] /= 10.0;
		
		//ABB
		
		for (int j = 0; j < 10; j++) {
			//primeiro, faco a insercao
			tempo = clock();
			for (int k = n[ni]-1; k >= 0; k--) insere_ABB(&estr4, k);
			tempo = clock() - tempo;
			tabela[1][3][ni] += tempo;
			
			//agora, faco a busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_ABB(estr4, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_ABB(estr4, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[7][3][ni] += tempo;
			
			destroi_ABB(&estr4);
			cria_ABB(&estr4);	//faco isso para "resetar" a estrutura
		}
		tabela[1][3][ni] /= 10.0;
		tabela[7][3][ni] /= 10.0;
			
		//AVL
		
		for (int j = 0; j < 10; j++) {
			//primeiro, faco a insercao
			tempo = clock();
			for (int k = n[ni]-1; k >= 0; k--) insere_AVL(&estr5, k);
			tempo = clock() - tempo;
			tabela[1][4][ni] += tempo;
			
			//agora, faco a busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_AVL(estr5, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_AVL(estr5, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[7][4][ni] += tempo;
			
			destroi_AVL(&estr5);
			cria_AVL(&estr5);	//faco isso para "resetar" a estrutura
		}
		tabela[1][4][ni] /= 10.0;
		tabela[7][4][ni] /= 10.0;

		//e LFREQ
		
		for (int j = 0; j < 10; j++) {
			//primeiro, faco a insercao
			tempo = clock();
			for (int k = n[ni]-1; k >= 0; k--) insere_LFREQ(&estr6, k);
			tempo = clock() - tempo;
			tabela[1][5][ni] += tempo;
			
			//agora, faco a busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_LFREQ(&estr6, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_LFREQ(&estr6, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[7][5][ni] += tempo;
			
			destroi_LFREQ(&estr6);
			cria_LFREQ(&estr6);	//faco isso para "resetar" a estrutura
		}
		tabela[1][5][ni] /= 10.0;
		tabela[7][5][ni] /= 10.0;
		
		
		//agora, so falta a insercao e remocao aleatorias
		
		//vamos comecar, de praxe, pela BB
		
		for (int j = 0; j < 10; j++) {
			count = 0;
			
			for (int k = 0; k < n[ni]; k++) usado[k] = 0;	// "reseto" o vetor de usados
			
			//primeiro, preparo os numeros aleatorios (isto eh feito para que o tempo da insercao aleatoria nao fique "encontrar os numeros aleatorios" + "inserir os numeros aleatorios", mas sim apenas "inserir os numeros aleatorios")
			do {
				n_ale = rand() % n[ni];
				if (usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 1;
				count++;
			} while (count < n[ni]);
			
			//agora sim, conto o tempo de insercao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) insere_BB(&estr1, numero[k]);
			tempo = clock() - tempo;
			tabela[2][0][ni] += tempo;
			
			//busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_BB(&estr1, n_ale, 0, n[ni]);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_BB(&estr1, n_ale, 0, n[ni]);
				}
			}
			tempo = clock() - tempo;
			tabela[8][0][ni] += tempo;
			
			//primeiro, preparo os numeros aleatorios (pelo mesmo motivo da insercao)
			count = 0;
			do {
				n_ale = rand() % n[ni];
				if (!usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 0;
				count++;
			} while (count < n[ni]/2);
			
			//agora, a remocao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				if (k < n[ni]/2) {	//para a primeira metade, faco remocao de numeros existentes
					remove_BB(&estr1, numero[k]);
				} else {	//para a outra metade, tento fazer a remocao de inexistentes
					n_ale = rand() + n[ni];
					remove_BB(&estr1, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[5][0][ni] += tempo;
			
			destroi_BB(&estr1);
			cria_BB(&estr1);	//faco isso para "resetar" a estrutura
		}
		tabela[2][0][ni] /= 10.0;
		tabela[8][0][ni] /= 10.0;
		tabela[5][0][ni] /= 10.0;
		
		//agora para a LO
		
		for (int j = 0; j < 10; j++) {
			count = 0;
			
			for (int k = 0; k < n[ni]; k++) usado[k] = 0;	// "reseto" o vetor de usados
			
			//primeiro, preparo os numeros aleatorios (isto eh feito para que o tempo da insercao aleatoria nao fique "encontrar os numeros aleatorios" + "inserir os numeros aleatorios", mas sim apenas "inserir os numeros aleatorios")
			do {
				n_ale = rand() % n[ni];
				if (usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 1;
				count++;
			} while (count < n[ni]);
			
			//agora sim, conto o tempo de insercao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) insere_LO(&estr2, numero[k]);
			tempo = clock() - tempo;
			tabela[2][1][ni] += tempo;
			
			//busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_LO(estr2, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_LO(estr2, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[8][1][ni] += tempo;
			
			//primeiro, preparo os numeros aleatorios (pelo mesmo motivo da insercao)
			count = 0;
			do {
				n_ale = rand() % n[ni];
				if (!usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 0;
				count++;
			} while (count < n[ni]/2);
			
			//agora, a remocao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				if (k < n[ni]/2) {	//para a primeira metade, faco remocao de numeros existentes
					remove_LO(&estr2, numero[k]);
				} else {	//para a outra metade, tento fazer a remocao de inexistentes
					n_ale = rand() + n[ni];
					remove_LO(&estr2, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[5][1][ni] += tempo;
			
			destroi_LO(&estr2);
			cria_LO(&estr2);	//faco isso para "resetar" a estrutura
		}
		tabela[2][1][ni] /= 10.0;
		tabela[8][1][ni] /= 10.0;
		tabela[5][1][ni] /= 10.0;
		
		//para a LOS
		
		for (int j = 0; j < 10; j++) {
			count = 0;
			
			for (int k = 0; k < n[ni]; k++) usado[k] = 0;	// "reseto" o vetor de usados
			
			//primeiro, preparo os numeros aleatorios (isto eh feito para que o tempo da insercao aleatoria nao fique "encontrar os numeros aleatorios" + "inserir os numeros aleatorios", mas sim apenas "inserir os numeros aleatorios")
			do {
				n_ale = rand() % n[ni];
				if (usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 1;
				count++;
			} while (count < n[ni]);
			
			//agora sim, conto o tempo de insercao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) insere_LOS(&estr3, numero[k]);
			tempo = clock() - tempo;
			tabela[2][2][ni] += tempo;
			
			//busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_LOS(estr3, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_LOS(estr3, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[8][2][ni] += tempo;
			
			//primeiro, preparo os numeros aleatorios (pelo mesmo motivo da insercao)
			count = 0;
			do {
				n_ale = rand() % n[ni];
				if (!usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 0;
				count++;
			} while (count < n[ni]/2);
			
			//agora, a remocao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				if (k < n[ni]/2) {	//para a primeira metade, faco remocao de numeros existentes
					remove_LOS(&estr3, numero[k]);
				} else {	//para a outra metade, tento fazer a remocao de inexistentes
					n_ale = rand() + n[ni];
					remove_LOS(&estr3, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[5][2][ni] += tempo;
			
			destroi_LOS(&estr3);
			cria_LOS(&estr3);	//faco isso para "resetar" a estrutura
		}
		tabela[2][2][ni] /= 10.0;
		tabela[8][2][ni] /= 10.0;
		tabela[5][2][ni] /= 10.0;
		
		//ABB
		
		for (int j = 0; j < 10; j++) {
			count = 0;
			
			for (int k = 0; k < n[ni]; k++) usado[k] = 0;	// "reseto" o vetor de usados
			
			//primeiro, preparo os numeros aleatorios (isto eh feito para que o tempo da insercao aleatoria nao fique "encontrar os numeros aleatorios" + "inserir os numeros aleatorios", mas sim apenas "inserir os numeros aleatorios")
			do {
				n_ale = rand() % n[ni];
				if (usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 1;
				count++;
			} while (count < n[ni]);
			
			//agora sim, conto o tempo de insercao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) insere_ABB(&estr4, numero[k]);
			tempo = clock() - tempo;
			tabela[2][3][ni] += tempo;
			
			//busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_ABB(estr4, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_ABB(estr4, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[8][3][ni] += tempo;
			
			//primeiro, preparo os numeros aleatorios (pelo mesmo motivo da insercao)
			count = 0;
			do {
				n_ale = rand() % n[ni];
				if (!usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 0;
				count++;
			} while (count < n[ni]/2);
			
			//agora, a remocao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				if (k < n[ni]/2) {	//para a primeira metade, faco remocao de numeros existentes
					remove_ABB(&estr4, numero[k]);
				} else {	//para a outra metade, tento fazer a remocao de inexistentes
					n_ale = rand() + n[ni];
					remove_ABB(&estr4, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[5][3][ni] += tempo;
			
			destroi_ABB(&estr4);
			cria_ABB(&estr4);	//faco isso para "resetar" a estrutura
		}
		tabela[2][3][ni] /= 10.0;
		tabela[8][3][ni] /= 10.0;
		tabela[5][3][ni] /= 10.0;
		
		//AVL
		
		for (int j = 0; j < 10; j++) {
			count = 0;
			
			for (int k = 0; k < n[ni]; k++) usado[k] = 0;	// "reseto" o vetor de usados
			
			//primeiro, preparo os numeros aleatorios (isto eh feito para que o tempo da insercao aleatoria nao fique "encontrar os numeros aleatorios" + "inserir os numeros aleatorios", mas sim apenas "inserir os numeros aleatorios")
			do {
				n_ale = rand() % n[ni];
				if (usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 1;
				count++;
			} while (count < n[ni]);
			
			//agora sim, conto o tempo de insercao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) insere_AVL(&estr5, numero[k]);
			tempo = clock() - tempo;
			tabela[2][4][ni] += tempo;
			
			//busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_AVL(estr5, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_AVL(estr5, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[8][4][ni] += tempo;
			
			//primeiro, preparo os numeros aleatorios (pelo mesmo motivo da insercao)
			count = 0;
			do {
				n_ale = rand() % n[ni];
				if (!usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 0;
				count++;
			} while (count < n[ni]/2);
			
			//agora, a remocao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				if (k < n[ni]/2) {	//para a primeira metade, faco remocao de numeros existentes
					remove_AVL(&estr5, numero[k]);
				} else {	//para a outra metade, tento fazer a remocao de inexistentes
					n_ale = rand() + n[ni];
					remove_AVL(&estr5, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[5][4][ni] += tempo;
			
			destroi_AVL(&estr5);
			cria_AVL(&estr5);	//faco isso para "resetar" a estrutura
		}
		tabela[2][4][ni] /= 10.0;
		tabela[8][4][ni] /= 10.0;
		tabela[5][4][ni] /= 10.0;
		
		//e, por ultimo, para a LFREQ
		
		for (int j = 0; j < 10; j++) {
			count = 0;
			
			for (int k = 0; k < n[ni]; k++) usado[k] = 0;	// "reseto" o vetor de usados
			
			//primeiro, preparo os numeros aleatorios (isto eh feito para que o tempo da insercao aleatoria nao fique "encontrar os numeros aleatorios" + "inserir os numeros aleatorios", mas sim apenas "inserir os numeros aleatorios")
			do {
				n_ale = rand() % n[ni];
				if (usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 1;
				count++;
			} while (count < n[ni]);
			
			//agora sim, conto o tempo de insercao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) insere_LFREQ(&estr6, numero[k]);
			tempo = clock() - tempo;
			tabela[2][5][ni] += tempo;
			
			//busca
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				n_ale = rand();
				if (k < n[ni]/2) {	//para a primeira metade, faco busca por numeros existentes
					n_ale = n_ale % n[ni];
					busca_LFREQ(&estr6, n_ale);
				} else {	//para a outra metade, faco por inexistentes
					n_ale += n[ni];
					busca_LFREQ(&estr6, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[8][5][ni] += tempo;
			
			//primeiro, preparo os numeros aleatorios (pelo mesmo motivo da insercao)
			count = 0;
			do {
				n_ale = rand() % n[ni];
				if (!usado[n_ale]) continue;
				numero[count] = n_ale;
				usado[n_ale] = 0;
				count++;
			} while (count < n[ni]/2);
			
			//agora, a remocao
			tempo = clock();
			for (int k = 0; k < n[ni]; k++) {
				if (k < n[ni]/2) {	//para a primeira metade, faco remocao de numeros existentes
					remove_LFREQ(&estr6, numero[k]);
				} else {	//para a outra metade, tento fazer a remocao de inexistentes
					n_ale = rand() + n[ni];
					remove_LFREQ(&estr6, n_ale);
				}
			}
			tempo = clock() - tempo;
			tabela[5][5][ni] += tempo;
			
			destroi_LFREQ(&estr6);
			cria_LFREQ(&estr6);	//faco isso para "resetar" a estrutura
		}
		tabela[2][5][ni] /= 10.0;
		tabela[8][5][ni] /= 10.0;
		tabela[5][5][ni] /= 10.0;
	}
	*/
	
	printf("\tTabela 1: Tempo de insercao crescente\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 2: Tempo de insercao decrescente\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 3: Tempo de insercao aleatoria\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 4: Tempo de remocao crescente (apos insercao crescente)\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 5: Tempo de remocao decrescente (apos insercao crescente)\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 6: Tempo de remocao aleatoria (apos insercao aleatoria)\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 7: Tempo de busca (apos insercao crescente)\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 8: Tempo de busca (apos insercao decrescente)\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	printf("\tTabela 9: Tempo de busca (apos insercao aleatoria)\n");
	printf("\tn=100\tn=1.000\tn=10.000\tn=100.000\n");
	printf("BB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][0][0], tabela[0][0][1], tabela[0][0][2], tabela[0][0][3]);
	printf("LO\t%lf\t%lf\t%lf\t%lf\n", tabela[0][1][0], tabela[0][1][1], tabela[0][1][2], tabela[0][1][3]);
	printf("LOS\t%lf\t%lf\t%lf\t%lf\n", tabela[0][2][0], tabela[0][2][1], tabela[0][2][2], tabela[0][2][3]);
	printf("ABB\t%lf\t%lf\t%lf\t%lf\n", tabela[0][3][0], tabela[0][3][1], tabela[0][3][2], tabela[0][3][3]);
	printf("AVL\t%lf\t%lf\t%lf\t%lf\n", tabela[0][4][0], tabela[0][4][1], tabela[0][4][2], tabela[0][4][3]);
	printf("LFREQ\t%lf\t%lf\t%lf\t%lf\n", tabela[0][5][0], tabela[0][5][1], tabela[0][5][2], tabela[0][5][3]);
	printf("-");
	
	
	//destroi_BB(&estr1);
	//destroi_LO(&estr2);
	//destroi_LOS(&estr3);
	//destroi_ABB(&estr4);
	//destroi_AVL(&estr5);
	//destroi_LFREQ(&estr6);
	//free(usado);
	//free(numero);

	return 0;
}
