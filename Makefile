all :
	gcc -o main BB.c LO.c LOS.c ABB.c AVL.c LFREQ.c main.c -std=c99 -g

run :
	./main
	
debug :
	gdb main
	
teste :
	./main > saida.txt
	gcc -o testaFormato testaFormato.c
	./testaFormato saida.txt

