typedef struct no_LO {
    int info;
    struct no_LO *prox;
} No_LO;

typedef struct {
    No_LO *ini;
} ListaOrd;

void cria_LO(ListaOrd *l);
void destroi_LO(ListaOrd *l);
int estavazia_LO(ListaOrd l);
int insere_LO(ListaOrd *l, int x);
int remove_LO(ListaOrd *l, int x);
int busca_LO(ListaOrd l, int x);
