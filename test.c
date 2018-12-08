#include <stdio.h>

#include "LFREQ.h"
//#include "BB.h"

int main() {
	
	LFREQ a;
	
	cria_LFREQ(&a);
	
	insere_LFREQ(&a,6);
	insere_LFREQ(&a,4);
	insere_LFREQ(&a,7);
	insere_LFREQ(&a,2);
	insere_LFREQ(&a,5);
	insere_LFREQ(&a,3);
	insere_LFREQ(&a,8);

	remove_LFREQ(&a,6);
	remove_LFREQ(&a,4);
	remove_LFREQ(&a,7);
	remove_LFREQ(&a,2);
	remove_LFREQ(&a,5);
	remove_LFREQ(&a,3);
	remove_LFREQ(&a,8);
	

	


	destroi_LFREQ(&a);


}
