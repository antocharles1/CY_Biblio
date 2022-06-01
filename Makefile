all : exec

menu.o : menu.c menu.h struct.h ttime.h 
	gcc -o menu.o -c menu.c 
	
save.o : save.c save.h struct.h menu.h
	gcc -o save.o -c save.c 

main.o : main.c menu.h ttime.h save.h
	gcc -o main.o -c main.c
	
exec : main.o save.o menu.o
	gcc main.o save.o menu.o -o exec
