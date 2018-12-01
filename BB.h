#define tam 1000000

typedef struct {
	int v[tam];
	int tam_atual;
} BB;

void cria_BB(BB *b);
void destroi_BB(BB *b);
int estavazia_BB(BB *b);
void insere_BB(BB *b, int x);
void remove_BB(BB *b, int x);
int busca_BB(BB *b, int chave, int ini, int fim);
