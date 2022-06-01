
typedef struct{			//Define a structure for books
	char title[100];
	char author[50];
	int genre;
	char id[50];
	int  loan;
	int h;
	int min;
	int sec;
}Book;

typedef struct{			//Define a structure for users
    char first_name[50];
    char login[50];
    char password[50];
    int type;
    int book_number;
    Book book_list[6];
    int blacklisted;
}User;
