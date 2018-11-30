all : main
	gcc main.c BB.c ABB.c LO.c LOS.c -o main 

run :
	./main

