typedef struct no_LFREQ {
    int info;
    struct no_LFREQ *ant, *prox;
} No_LFREQ;

typedef struct {
    No_LFREQ *ini, *fim;
} LFREQ;

void cria_LFREQ(LFREQ *l);
void apaga_LFREQ(LFREQ *l);
int insere_LFREQ(LFREQ *l, int x);
int busca_LFREQ(LFREQ *l, int x);
void retira_LFREQ(LFREQ *l, int x);
void imprime(LFREQ l);