all :
	gcc -o main BB.c LO.c LOS.c ABB.c AVL.c main.c -std=c99

run :
	./main
	
teste :
	./main > saida.txt
	gcc -o testaFormato testaFormato.c
	./testaFormato saida.txt

