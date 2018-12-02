#include <stdio.h>

#include "AVL.h"

int main() {
	
	AVL a;
	
	cria_AVL(&a);
	
	insere_AVL(&a,6);
	insere_AVL(&a,4);
	insere_AVL(&a,7);
	insere_AVL(&a,2);
	insere_AVL(&a,5);
	insere_AVL(&a,3);
	insere_AVL(&a,8);
	
	remove_AVL(&a,8);
		
	destroi_AVL(&a);


}
