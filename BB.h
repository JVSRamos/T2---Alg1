#define tam 100

typedef struct vet {

	int v[tam];
	int tam_atual;

}Vet;


void cria_BB(Vet* b);
void insere_BB(Vet* b, int x);
void retira_BB(Vet* b, int x);
int busca_binaria(Vet* b, int chave, int ini, int fim);