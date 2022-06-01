#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<time.h>
#include"menu.h"
#define SPACE 500
#define SPACE_BOOK 100






void Write(User a){		//procedure to save a new user into the database
	FILE* base;
	base=fopen("base.txt","ab");  		//saves the info in binary for security
	fwrite(&a,sizeof(User),1,base);
	fclose(base);
}





void Rewrite(User a){			//procedure that saves the info of the users inside our database
	int i;
	FILE* base;
	long oct;
	User readtable[SPACE];
	base=fopen("base.txt","rb+");
	rewind(base);
	for(i=0;i<=SPACE;i++){			// this loop is to find the users place in the database 
		fread(&readtable[i],sizeof(User),1,base);
		if(strcmp(a.login,readtable[i].login)==0){
			oct=ftell(base);
		
		}
		
	}
	fseek(base,oct-sizeof(User),SEEK_SET); //  rewrites the information of the users
	fwrite(&a,sizeof(User),1,base);
	fclose(base);
}




void Read_Book(Book tab[]){			//procedure to save into the program the informations of the books
	
	FILE* base;
	int i;
	base=fopen("books.txt","rb");
	rewind(base);
	for(i=0;i<=SPACE_BOOK;i++){		// this loop saves each book
		fread(&tab[i],sizeof(Book),1,base);
	}
	fclose(base);
}

void Rewrite_Book(Book a){		//procedure that saves when a book is borrowed or not into the database 
	FILE* base;
	long oct;
	Book readbook[SPACE_BOOK];
	base=fopen("books.txt","rb+");
	rewind(base);
	for(int i=0;i<=SPACE_BOOK;i++){
		fread(&readbook[i],sizeof(Book),1,base);   // this loop searches for the info of the book
		if(strcmp(a.title,readbook[i].title)==0){
			oct=ftell(base);
		}
	}
	fseek(base,oct-sizeof(Book),SEEK_SET);  //rewrites all the information on the book
	fwrite(&a,sizeof(Book),1,base);
	fclose(base);

}


void Record_Book(){			// procedure that saves new books into our database
	Save_Book_Menu_Poster();
	Book new;
	char gender;
	printf("Don't forget to put an underscore _ when you put a space at any moment,thank you!");
	printf("\nAUTHOR'S NAME : ");
	scanf("%s",new.author);
	while(gender!='1' && gender!='2' && gender!='3' && gender!='4' && gender!='5' && gender!='6'){
		printf("\nLITERARY GENRE: \nTAP 1 FOR ROMANTIC\nTAP 2 FOR ACTION\nTAP 3 FOR SCIENTIFIC\nTAP 4 FOR SCIENCE FICTION\nTAP 5 FOR COMICAL\nTAP 6 FOR OTHER\n ");
		scanf("%s",&gender);
		
	}
	new.genre=atoi(&gender);
	printf("\nCODE ID : ");
	scanf("%s",new.id);
	printf("\nTITLE'S BOOK :");
	scanf("%s",new.title);
	new.loan=1;
	FILE* base;
	base=fopen("books.txt","ab");
	fwrite(&new,sizeof(Book),1,base);
	fclose(base);
}



void Read_Base(User tab[]){		//procedure goes into the database and collects all users and places them into the board
	FILE* base;
	int i;
	base=fopen("base.txt","rb");
	rewind(base);
	for(i=0;i<=SPACE;i++){
		fread(&tab[i],sizeof(User),1,base);
	}
}











