#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Book{
        size_t bookId;
        char issuedDate[11];
        char bookName[100];
        struct Book* next;
};

void getDate(char *date, size_t size){
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(date,size,"%d/%m/%Y",t);
}

void AddBook(struct Book* Library, size_t id, const char* name,const char* date){
        struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
        newBook->bookId = id;
        strcpy(newBook->issuedDate,date);
        strcpy(newBook->bookName,name);
        struct Book* temp = Library;
        newBook->next = NULL;
        while(temp->next) temp = temp->next;
        temp->next = newBook;
}

bool issuedToday(struct Book* Library,size_t id ){
    char today[11];
    getDate(today,sizeof(today));
    struct Book* temp = Library;
    while(temp){
            if(temp->bookId == id) return strcmp(temp->issuedDate,today) == 0;
            temp = temp->next;
    }
    return false;
}

void Print(bool boolean, int id){
        printf("The Book with id %d was ",id);  
        if(boolean){
                printf("issued Today\n");
        }
        else printf("not issued Today\n");
}

int main(){
        struct Book* Library = (struct Book*)malloc(sizeof(struct Book));
        Library->bookId = -1;
        Library->next = NULL;
        char date[11];
        getDate(date,sizeof(date));
        AddBook(Library, 91, "Book A", "12/12/2000");
        AddBook(Library, 37, "Book B", date);
        AddBook(Library, 58, "Book C", "03/05/2010");
        AddBook(Library, 12, "Book D", date);
        AddBook(Library, 76, "Book E", "21/07/2005");
        AddBook(Library, 44, "Book F", "11/11/2011");
        AddBook(Library, 29, "Book G", date);
        AddBook(Library, 83, "Book H", "09/09/2009");
        AddBook(Library, 65, "Book I", "14/02/2014");
        AddBook(Library, 18, "Book J", date);
        AddBook(Library, 97, "Book K", "30/06/2001");
        AddBook(Library, 41, "Book L", "08/03/2008");
        AddBook(Library, 22, "Book M", date);
        AddBook(Library, 73, "Book N", "17/12/2012");
        AddBook(Library, 56, "Book O", "25/04/2004");
        AddBook(Library, 34, "Book P", "19/01/2003");
        AddBook(Library, 88, "Book Q", date);
        AddBook(Library, 11, "Book R", "07/07/2007");
        AddBook(Library, 62, "Book S", "13/10/2013");
        AddBook(Library, 49, "Book T", date);
        AddBook(Library, 95, "Book U", "28/08/2002");
        AddBook(Library, 27, "Book V", "05/05/2006");
        AddBook(Library, 70, "Book W", date);
        AddBook(Library, 16, "Book X", "22/11/2015");
        AddBook(Library, 53, "Book Y", "01/01/2000");
        AddBook(Library, 84, "Book Z", date);
        bool book1 = issuedToday(Library,53);
        Print(book1,53);
        bool book2 = issuedToday(Library,84);
        Print(book2,84);
        struct Book* temp = Library;
        while(temp){
                struct Book* next = temp->next;
                free(temp);
                temp = next;
        }
        return 0;
}

        

