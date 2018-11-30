typedef struct no_ABB {
    int info;
    struct no_ABB *esq, *dir;
} No_ABB;

typedef struct {
    No_ABB *raiz;
} ABB;

void cria_ABB(ABB *a);
void destroi_ABB(ABB *a);
int vazia(ABB a);
int busca_ABB(ABB a, int x);
int insere_ABB(ABB *a, int x);
int remove_ABB(ABB *a, int x);
