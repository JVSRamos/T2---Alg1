typedef int elem;

typedef struct no_AVL {
    elem info;
    struct no_AVL *esq, *dir;
    int fb;
} No_AVL;

typedef struct {
    No_AVL *raiz;
} AVL;

void cria_AVL(AVL *a);
void destroi_AVL(AVL *a);
int estavazia_AVL(AVL a);
int insere_AVL(AVL *a, elem x);
int remove_AVL(AVL *a, elem x);
int busca_AVL(AVL a, elem x);
void imprime_AVL(AVL a);	//remover depois
void emOrdem_AVL(AVL a);	//remover depois
