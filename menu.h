#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include"save.h"
				//initialize these 3 procedures to use them in any ordre in our program
void Teacher_Menu(User* tab, int place,int b);	
	
void Student_Menu(User* tab,int place,int b);

void connection(User tab[]);

void Create_Account(User tab[]);

void start(User tab[],int b);

void vide_buffer();

void Connection_Menu_Poster();


void Create_Account_Menu_Poster();


void Start_Menu_Poster(int a);


void Student_Menu_Poster(char prenom[],int a);


void Teacher_Menu_Poster(char prenom[],int a);

void Save_Book_Menu_Poster();

void exitt();
