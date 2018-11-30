typedef struct no_LOS {
    int info;
    struct no_LOS *prox;
} No_LOS;

typedef struct {
    No_LOS *ini, *sentinela;
} ListaOrds;

int cria_LOS(ListaOrds *l);
void destroi_LOS(ListaOrds *l);
int insere_LOS(ListaOrds *l, int x);
int remove_LOS(ListaOrds *l, int x);
int busca_LOS(ListaOrds l, int x);
int estavazia(ListaOrds l);
