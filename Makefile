# Created by Xiaotian Li on Aug 21, 2020
# A make file for Assignment 1

dict: main.o list.o dictFunctions.o
	gcc -o dict main.o list.o dictFunctions.o

list.o: list.c list.h dictFunctions.h
	gcc -c -Wall list.c

dictFunctions.o: dictFunctions.c dictFunctions.h
	gcc -c -Wall dictFunctions.c

main.o: main.c list.h
	gcc -c -Wall main.c


