#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include "menu.h"
#include<time.h>
#include"ttime.h"
#define SPACE 500
#define SPACE_BOOK 100


void vide_buffer(){			//to debug scanf	
	while(getc(stdin)!='\n'){

	}
}


void start(User tab[],int b){
					//procedure gives to the user the first menu where they choose if they wanna log in, create a account and to leave
	char a='7';
	Start_Menu_Poster(b);
	scanf("%c",&a); 
	if(a=='1'){
    		Read_Base(tab);
        	connection(tab);
    	}
        
    	else if (a=='2'){
    		Read_Base(tab);
        	Create_Account(tab);
		vide_buffer();
        	start(tab,1);
        }
        
    	else if (a=='3'){
        	exitt();
    	}
    	
    	else{
    		vide_buffer();
		start(tab,2);
	} 	
}  



void Student_Menu(User* tab,int place,int b){			//procedure which gives access to the student's menu
	char a;
	int i;
	scanf("%c",&a);
	Book tab_livre[SPACE_BOOK];
	if(a=='1'&& tab[place].book_number>0){
							//return book
		char choice;
		int c=40;
		int d=0;
		
		Read_Book(tab_livre);
		Book Book_List_New[6];
		while(c>tab[place].book_number){
			printf("\nCHOOSE THE BOOK'S NUMBER TO RETURN : \n");
			scanf("%s",&choice);
			c=atoi(&choice);
		}
		c-=1;
		for(i=0;i<=SPACE_BOOK;i++){			//compares the book's title and rewrites the book which has just been returned back into the books you can borrow
			if(strcmp(tab_livre[i].title,tab[place].book_list[c].title)==0){
				tab_livre[i].loan=1;
				Rewrite_Book(tab_livre[i]);
			}
			
		}
		for(i=0;i<=2;i++){				//When you return a book, this book is then well organized back into the existing book's list
			Book_List_New[i]=tab[place].book_list[i];
		}
		for(i=0;i<=2;i++){
			if(i!=c){
				if(d==1){
					tab[place].book_list[i-1]=Book_List_New[i];
				}
				else if(d==0){
					tab[place].book_list[i]=Book_List_New[i];
				}	
			}
			else if(i==c){
				d=1;
			}
			if(i==2){
				tab[place].book_list[i]=tab[place].book_list[5];
			}	
		
		}
		tab[place].book_number-=1;
		Rewrite(tab[place]);
		Student_Menu(tab,place,4);	  		// returns you back to the menu
	}
	else if(a=='2'){
								//borrow book
		if(tab[place].book_number<=2){
			int h,min,sec;
			char number;
			for(int j=0;j<=2;j++){
				return_time(&h,&min,&sec);
				if(tab[place].book_list[j].h<=24 &&tab[place].book_list[j].h>0){
					gap_time(&h,&min,&sec,tab[place].book_list[j].h,tab[place].book_list[j].min,tab[place].book_list[j].sec);
					if(sec >=120){
						tab[place].blacklisted=1;  //if the book isn't returned in the correct time, you can no longer borrow 
					}
				}
			}
			if(tab[place].blacklisted!=1){ // when the book has been return in the right time, you aren't blacklisted
				int a;
				char number;
				int numbere;
				time_t crt;
				Read_Book(tab_livre);
				while(number!='1' && number!='2' && number!='3' && number!='4' && number!='5' && number!='6'){
					printf("What category of books do you want to borrow ?\nTAP 1 FOR ROMANTIC\nTAP 2 FOR ACTION\nTAP 3 FOR SCIENTIFIC\nTAP 4 FOR SCIENCE FICTION\nTAP 5 FOR COMICAL\nTAP 6 FOR OTHER\n ");
					
					scanf("%s",&number);
				}
				numbere=atoi(&number);
				for(i=0;i<=SPACE_BOOK;i++){
					if(tab_livre[i].genre==numbere && tab_livre[i].loan==1){  				// shows the books that are available to borrow
						printf("\n %d :%s written by %s, the id code is %s\n",i+1,tab_livre[i].title,tab_livre[i].author,tab_livre[i].id);
				
					}
				}
				printf("\nbook number to borrow ?\n ");
				scanf("%s",&number);
				a=atoi(&number);
				tab[place].book_list[tab[place].book_number]=tab_livre[a-1];
				return_time(&tab[place].book_list[tab[place].book_number].h,&tab[place].book_list[tab[place].book_number].min,&tab[place].book_list[tab[place].book_number].sec);
				tab[place].book_number+=1;
				tab_livre[a-1].loan=2;
				Rewrite_Book(tab_livre[a-1]);
				Rewrite(tab[place]);
				Student_Menu(tab,place,0);
			}
		
			else if(tab[place].blacklisted==1){
				Student_Menu(tab,place,1);
		}
		}
		else{
			Student_Menu(tab,place,2);
		}
	}
	else if(a=='3'){
		exitt();
	}
	else{
		Student_Menu_Poster(tab[place].first_name,b);
		printf("\n YOUR BOOKS :\n\n");
		for(i=0;i<=2;i++){
			if(tab[place].book_list[i].loan==1){
				printf("Book number %d :%s borrowed at %d:%d:%d \n",i+1,tab[place].book_list[i].title,tab[place].book_list[i].h,tab[place].book_list[i].min,tab[place].book_list[i].sec);

			}
			else{
				printf("Book number %d : ----- \n",i+1);
			}
		}
		Student_Menu(tab,place,0);
	}
}





void Teacher_Menu(User* tab, int place,int b){   //procedure that operates the teacher menu
	char a;
	int i;
	Book* tab2;
	scanf("%c",&a);
	Book tab_livre[SPACE_BOOK];
	if(a=='1'){ 				// to save a book
		Record_Book();
		Teacher_Menu(tab,place,5);
	}
	
	else if(a=='2'&& tab[place].book_number>0){
						//return book
		char choice;
		int c=40;
		int d=0;
		Read_Book(tab_livre);
		Book Book_List_New[6];
		while(c>tab[place].book_number){
		printf("\nCHOOSE THE BOOK'S NUMBER TO RETURN : \n");
		scanf("%s",&choice);
		c=atoi(&choice);
		}						
		c-=1;
		for(i=0;i<=SPACE_BOOK;i++){
			if(strcmp(tab_livre[i].title,tab[place].book_list[c].title)==0){
				tab_livre[i].loan=1;
				Rewrite_Book(tab_livre[i]);
			}
			
		}
		for(i=0;i<=4;i++){
			Book_List_New[i]=tab[place].book_list[i];
		}
		for(i=0;i<=4;i++){
			if(i!=c){
				if(d==1){
					tab[place].book_list[i-1]=Book_List_New[i];
				}
				else if(d==0){
					tab[place].book_list[i]=Book_List_New[i];
				}	
			}
			else if(i==c){
				d=1;
			}
			if(i==4){
				tab[place].book_list[i]=tab[place].book_list[5];
			}	
		
		}
		tab[place].book_number-=1;
		Rewrite(tab[place]);
		Teacher_Menu(tab,place,4);	
	}	
	
	else if(a=='3'){
									//borrow books
		if(tab[place].book_number<=4){
			int h,min,sec;
			char number;
			for(int j=0;j<=4;j++){
				return_time(&h,&min,&sec);
				if(tab[place].book_list[j].h<=24 &&tab[place].book_list[j].h>0){
					gap_time(&h,&min,&sec,tab[place].book_list[j].h,tab[place].book_list[j].min,tab[place].book_list[j].sec);
					if(sec >=180){
						tab[place].blacklisted=1;
					}
				}
			}
			if(tab[place].blacklisted!=1){
				int a;
				char number;
				int numbere;
				Read_Book(tab_livre);
				while(number!='1' && number!='2' && number!='3' && number!='4' && number!='5' && number!='6'){
					printf("What category of books do you want to borrow ?\nTAP 1 FOR ROMANTIC\nTAP 2 FOR ACTION\nTAP 3 FOR SCIENTIFIC\nTAP 4 FOR SCIENCE FICTION\nTAP 5 FOR COMICAL\nTAP 6 FOR OTHER\n ");
					
					scanf("%s",&number);
				}
				numbere=atoi(&number);
				for(i=0;i<=SPACE_BOOK;i++){
					if(tab_livre[i].genre==numbere && tab_livre[i].loan==1){
						printf("\n %d :%s written by %s, the id code is %s\n",i+1,tab_livre[i].title,tab_livre[i].author,tab_livre[i].id);
					}
				}
				printf("\nbook number to borrow ?\n ");
				scanf("%s",&number);
				a=atoi(&number);
				a-=1;
				tab[place].book_list[tab[place].book_number]=tab_livre[a];
				return_time(&tab[place].book_list[tab[place].book_number].h,&tab[place].book_list[tab[place].book_number].min,&tab[place].book_list[tab[place].book_number].sec);
				tab[place].book_number+=1;
				tab_livre[a].loan=2;
				Rewrite_Book(tab_livre[a]);
				Rewrite(tab[place]);
				Teacher_Menu(tab,place,3);
			}
		
			else if(tab[place].blacklisted==1){
				Teacher_Menu(tab,place,1);
			}
		}
		else{
			Teacher_Menu(tab,place,2);
		}
	}
	else if(a=='4'){
		exitt();
	}
	else{
		Teacher_Menu_Poster(tab[place].first_name,b);
		printf("\n YOUR BOOKS :\n\n");
		for(i=0;i<=4;i++){
			if(tab[place].book_list[i].loan==1){
				printf("Book number %d :%s borrowed at %d:%d:%d \n",i+1,tab[place].book_list[i].title,tab[place].book_list[i].h,tab[place].book_list[i].min,tab[place].book_list[i].sec);

			}
			else{
				printf("Book number %d : ----- \n",i+1);
			}
		}
		Teacher_Menu(tab,place,0);
	}
}




void connection(User tab[]){			//procedure to connect the users to their dedicated menu
	char login[50];
	char password[50];
	int i,place;
	User c;
	int trouve=0;
	Connection_Menu_Poster();		//prints the general connecting menu
	scanf("%s",login);
	for(i=0;i<=SPACE;i++){
		if(strcmp(login,tab[i].login)==0){ 	//searchs in the board to find  where the user's information is saved
			trouve=1;			// condition which asks for the user's password if his account isfound in the board
			printf("\n\nHello %s !\n",tab[i].first_name);
			printf("\nEnter your password : ");
			scanf("%s",password);
			printf("\n\n\n");
			if(strcmp(password,tab[i].password)==0){ //
				printf("\nconnection done !\n");
				c=tab[i];
				place=i;
			}
    	    
			else{
				vide_buffer();
				start(tab,4);
			}
		}
	}
	if(trouve==0){
		vide_buffer();
		start(tab,3);
	}
    
	if(c.type==1){
		Teacher_Menu(tab,place,0);
		
	}
	if(c.type==2){
		Student_Menu(tab,place,0);
	}
}


void Create_Account(User tab[]){				//procedure which controls each account created 
	char q='4';
	User  a;
	int i;
	scanf("%c",&q);
	if(q=='1'){ 						// to create a teacher account
		a.type=1;
		printf("\n\n\n\n\n\nFIRST NAME: ");
		scanf("%s",a.first_name);
		printf("\n\nLOGIN : ");
		scanf("%s",a.login);
		for(i=0;i<=SPACE;i++){
			while(strcmp(a.login,tab[i].login)==0){				//compares with the existing logins to not have 2 times the same login
				printf("\nLOGIN ALREADY TAKEN !\nCHOOSE NEW : ");
				scanf("%s",a.login);
			}
		}
		printf("\nPASSWORD : ");
		scanf("%s",a.password);
		a.book_number=0;
		Write(a);
	}
	
	else if(q=='2'){					// to create a student account
		a.type=2;
		printf("\n\n\n\n\n\nFIRST NAME : ");
		scanf("%s",a.first_name);
		printf("\n\nLOGIN : ");
		scanf("%s",a.login);
		for(i=0;i<=SPACE;i++){
			while(strcmp(a.login,tab[i].login)==0){			// same as for the teacher 
				printf("\nLOGIN ALREADY TAKEN !\nCHOOSE NEW : ");
				scanf("%s",a.login);
			}
		}
		printf("\nPASSWORD : ");
		scanf("%s",a.password);
		a.book_number=0;
		Write(a);
	}
	else if(q=='3'){  			// to log out
		exitt();
    	}
    	
	else{					// in case the user doesn't do any of the 3 numbers, we send back the menu
		Create_Account_Menu_Poster();
		Create_Account(tab);
	}
}


void Connection_Menu_Poster(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n****************************\n\nLOG IN     MENU\n\n****************************\n\n");
	printf("\nEntrer your login : ");


}

void Create_Account_Menu_Poster(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n****************************\n\nMENU  CREATE YOUR ACCOUNT\n\n****************************\n\n\n\n");
		printf("\n *********************       *********************        **********\n");
		printf(" *TEACHER ACCOUNT: 1 *       *STUDENT ACCOUNT: 2 *        *MENU : 3*");
		printf("\n *********************       *********************        **********\n\n\n\n");


}

void Start_Menu_Poster(int a){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	if(a==4){
		printf("\nwrong password, back to main menu !\n");
	}
	printf("\n****************************\n\nMAIN MENU\n\n****************************\n\n");

	printf("**********************    ***************************    ****************\n*  LOG IN: TYPE 1    *    *CREATE AN ACCOUNT: TYPE 2*    *EXIT : TYPE 3 *\n**********************    ***************************    ****************\n");
	if(a==1){
		printf("\n\nYOUR ACCOUNT HAS BEEN CREATED \n");
	}
	else if(a==3){
		printf("\n\nno login, please create an account \n");
	}
	else if(a==2){
		printf("\n\nPlease choose a good number \n");
	}
	printf("\n\n\n\n\n\n");

}


void Student_Menu_Poster(char prenom[],int a){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n****************************\n\nSTUDENT MENU \n\n****************************\n\n");
	printf("HELLO %s !\n",prenom);
	printf("\n**********************        *******************       ************** \n");
	printf(  "*  RETURN BOOK : 1   *        * BORROW BOOK : 2 *       *  EXIT : 3  * ");
	printf("\n**********************        *******************       ************** \n\n");
	if(a==4){
		printf("RETURNED BOOK !\n");
	}
	else if(a==2){
		printf("You can't borrow a new book because you have already three books\n");
	}
	else if(a==1){
		printf("You've taken too much time to return your book, you can no longer borrow any more books\n");
	}
	else if(a==4){
		printf("RETURNED BOOK !\n");
	}
		
}

void Teacher_Menu_Poster(char prenom[],int a){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n****************************\n\nTEACHER MENU\n\n****************************\n\n");
	printf("HELLO %s !\n",prenom);
	printf("\n*********************          ******************        *****************\n");
	printf("*SAVE A NEW BOOK : 1*          * RETURN BOOK: 2 *        *BORROW BOOK : 3*");
	printf("\n*********************          ******************        *****************\n\n");
	printf("                               ***************\n");
	printf("                               * LOG OUT : 4 *\n");
	printf("                               ***************\n\n");
	if(a==5){
		printf("RECORDED BOOK !\n");
	}
	else if(a==4){
		printf("RETURNED BOOK !\n");
	}
	else if(a==2){
		printf("You can't borrow a new book because you have already five books\n");
	}
	else if(a==1){
		printf("You've taken too much time to return your book, you can no longer borrow any more books\n");
	}	
}


void Save_Book_Menu_Poster(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n****************************\n\n SAVE A NEW BOOK \n\n****************************\n\n");

}
void exitt(){
	printf("\n YOU HAVE BEEN LOGGED OUT SUCCESSFULLY!\n");
}















