#include <stdio.h>
#include <windows.h>

void book_menu(void);
void add_book(void);
void edit_book(void);
void book_record(void);
void search_book(void);

int getdata(void);
int checkid(int);


// structure for book
struct book{

    int book_id;
    char book_name[50];
    char book_author[50];
    int quantity;
    int rack_number;
    float price;
    char cat[50];

};
struct book b;

// file pointer
FILE *fp;


// book menu
void book_menu(void){

    int choice = 0;

    system("cls");

    gotoxy(5,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  BOOK MENU  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");


    gotoxy(5,8);
    printf("\xDB\xDB\xDB 1. ADD BOOK");
    gotoxy(5,10);
    printf("\xDB\xDB\xDB 2. EDIT BOOK");
    gotoxy(5,12);
    printf("\xDB\xDB\xDB 3. BOOK RECORD");
    gotoxy(5,14);
    printf("\xDB\xDB\xDB 4. SEARCH BOOK");
    gotoxy(5,16);
    printf("\xDB\xDB\xDB 5. GO BACK TO LIBRARY MENU");
    gotoxy(5,18);
    printf("\xDB\xDB\xDB 6. EXIT");
    gotoxy(5,20);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5,24);
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch(choice){

    case 1:
        add_book();
        break;

    case 2:
        edit_book();
        break;

    case 3:
        book_record();
        break;

    case 4:
        search_book();
        break;

    case 5:
        library_menu();
        break;

    case 6:
        exit(0);
        break;

    default:
        gotoxy(5,22);
        printf("INVALID CHOICE !");
        Sleep(500);
        book_menu();
    }

    return 0;

}

// Function to add book
void add_book(void){

    char ch;
    int choice;

    system("cls");

    fp = fopen("book_data.dat", "ab+");

    // getting data to be written in files
    if(getdata() == 1){
        // choosing the category of book
        fseek(fp, 0, SEEK_END);
        fwrite(&b, sizeof(b), 1, fp);
        fclose(fp);

        gotoxy(5, 23);
        printf("RECORDING DATA IS SUCCESSFUL !!");

    }

    gotoxy(5,26);
    printf("Do you want to add another book?(y/n) ");
    getchar();
    scanf("%c", &ch);

    if(ch == 'y' || ch == 'Y')
        add_book();

    else if(ch == 'n' || ch == 'N')
        book_menu();

    else{
        gotoxy(5,30);
        printf("INVALID CHOICE !!");
        Sleep(500);
        add_book();
    }

    return 0;
}

int id;                // temporary book id variable


// getting the data from user
int getdata(void){

    gotoxy(5,2);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  ADD BOOK  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5,8);
    printf("ENTER BOOK ID: ");
    scanf("%d", &id);

    // calling the function to check id
    if(checkid(id) == 0){
        gotoxy(5,20);
        printf("BOOK ALREADY EXISTS !!");
        getchar();
        return 0;
    }

    // if book_id is not in record
    b.book_id = id;

    gotoxy(5,10);
    printf("ENTER CATEGORIES: ");
    fflush(stdin);
    fgets(b.cat, 50, stdin);

    gotoxy(5,12);
    printf("ENTER BOOK NAME: ");
    fflush(stdin);
    fgets(b.book_name, 50, stdin);

    gotoxy(5,14);
    printf("ENTER BOOK AUTHOR: ");
    fflush(stdin);
    fgets(b.book_author, 50, stdin);

    gotoxy(5,16);
    printf("ENTER BOOK QUANTITY: ");
    scanf("%d", &b.quantity);

    gotoxy(5,18);
    printf("ENTER BOOK PRICE: ");
    scanf("%f", &b.price);

    gotoxy(5,20);
    printf("ENTER RACK NUMBER: ");
    scanf("%d", &b.rack_number);


    return 1;

}

// checking entered book id
int checkid(int id){
    // rewinding file pointer back to the start of the file
    rewind(fp);

    // reading from the file
    while(fread(&b, sizeof(b), 1, fp) == 1){
        // if book id is found
        if(b.book_id == id)
            return 0;
    }

    return 1;
}


// book record
void book_record(void){

    int total_books = 0, row;

    system("cls");

    gotoxy(5,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  BOOKS RECORD  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5,8);
    printf("CATEGORY         BOOK ID         BOOK NAME         AUTHOR         QUANTITY         PRICE         RACK NUMBER");      // 5 spaces

    fp = fopen("book_data.dat", "rb");

    rewind(fp);

    row = 10;

    if(fp == NULL)
        printf("\n\nUnable to open file");

    while(fread(&b, sizeof(b), 1, fp) == 1){
        gotoxy(5, row);
        printf("%s", b.cat);
        gotoxy(25, row);
        printf("%d", b.book_id);
        gotoxy(38, row);
        printf("%s", b.book_name);
        gotoxy(56, row);
        printf("%s", b.book_author);
        gotoxy(73, row);
        printf("%d", b.quantity);
        gotoxy(88, row);
        printf("$%.2f", b.price);
        gotoxy(107, row);
        printf("%d", b.rack_number);

        row += 2;
        total_books += b.quantity;
    }

    gotoxy(5, 25);
    printf("Total Books = %d", total_books);

    gotoxy(5, 27);
    printf("Press Enter to go back to book menu !");
    fflush(stdin);
    getchar();

    // book menu
    book_menu();

    fclose(fp);

}


// function to search for books in the record
void search_book(void){

    int id;
    char choice;
    int  findbook = 0;

    system("cls");

    gotoxy(5,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  SEARCH BOOKS  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5,8);
    printf("Enter ID: ");
    scanf("%d", &id);

    fp = fopen("book_data.dat", "rb+");

    rewind(fp);



    while(fread(&b, sizeof(b), 1, fp) == 1){
        // if entered id matches any id in the record
        if(b.book_id == id){
            gotoxy(5,14);
            printf("BOOK IS FOUND !");
            gotoxy(5, 16);
            printf("PRESS ENTER TO GET DETAILS !");
            fflush(stdin);
            getchar();

            system("cls");

            // Printing book record
            gotoxy(5,4);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  SEARCH BOOKS  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(5,8);
            printf("Book Category: %s", b.cat);
            gotoxy(5,10);
            printf("Book name: %s", b.book_name);
            gotoxy(5,12);
            printf("Book Author: %s", b.book_author);
            gotoxy(5,14);
            printf("Quantity: %d", b.quantity);
            gotoxy(5,16);
            printf("Price: $ %.2f", b.price);
            gotoxy(5,18);
            printf("Rack number: %d", b.rack_number);
            gotoxy(5,22);


            do{
                printf("Do you want to search another book?(y/n) ");
                fflush(stdin);
                scanf("%c", &choice);

                if(choice == 'y' || choice == 'Y')
                    search_book();

                else if(choice == 'n' || choice == 'N')
                    book_menu();

                else{
                    printf("\n     Invalid Choice ! ");
                    printf("\n     ");
                }
            }
            while(choice != 'y' || choice != 'Y' || choice != 'n' || choice != 'N');


        // if book is found and properly displayed
        findbook = 1;
        }

    }

    if(findbook != 1){
        gotoxy(20,14);
        printf("NO RECORD IS FOUND !");
    }

    gotoxy(5, 22);
    do{
            printf("Do you want to search another book?(y/n) ");
            fflush(stdin);
            scanf("%c", &choice);

            if(choice == 'y' || choice == 'Y')
                search_book();

            else if(choice == 'n' || choice == 'N')
                book_menu();

            else{
                printf("\n     Invalid Choice ! ");
                printf("\n     ");
            }

        }
        while(choice != 'y' || choice != 'Y' || choice != 'n' || choice != 'N');



    fclose(fp);

    getchar();
}


// Function to edit book in a record
void edit_book(void){

    int flag = 0;
    int id;
    char another = 'y';

    system("cls");



    while(another == 'y'){

        system("cls");

        gotoxy(5,4);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  EDIT BOOK RECORD  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(5,8);
        printf("ENTER BOOK ID TO EDIT: ");
        scanf("%d", &id);

        fp = fopen("book_data.dat", "rb+");

        if(fp == NULL){
            printf("Unable to open file");
            exit(0);
        }

        while(fread(&b, sizeof(b), 1, fp) == 1){
            if(checkid(id) == 0){
                gotoxy(20,14);
                printf("BOOK IS AVAILABLE !");
                gotoxy(5, 16);
                printf("Press Enter to continue !");
                fflush(stdin);
                getchar();

                system("cls");

                gotoxy(5,3);
                printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  EDIT BOOK RECORD  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
                gotoxy(5,8);
                printf("ENTER BOOK CATEGORY: ");
                fflush(stdin);
                fgets(b.cat, 50, stdin);

                gotoxy(5,10);
                printf("ENTER NEW BOOK NAME: ");
                fflush(stdin);
                fgets(b.book_name, 50, stdin);

                gotoxy(5,12);
                printf("ENTER NEW BOOK AUTHOR: ");
                fflush(stdin);
                fgets(b.book_author, 50, stdin);

                gotoxy(5,14);
                printf("ENTER NEW BOOK QUANTITY: ");
                scanf("%d", &b.quantity);

                gotoxy(5,16);
                printf("ENTER NEW BOOK PRICE: ");
                scanf("%f", &b.price);

                gotoxy(5,18);
                printf("ENTER NEW RACK NUMBER: ");
                scanf("%d", &b.rack_number);

                gotoxy(20,24);
                printf("THE RECORD IS MODIFIED !");

                fseek(fp, ftell(fp) - sizeof(b), 0);
                fwrite(&b, sizeof(b), 1, fp);

                fclose(fp);

                flag = 1;

            }

            if(flag == 0){
                gotoxy(20,14);
                printf("NO RECORD FOUND !");
            }
        }

        gotoxy(5, 26);
        do{

            printf("Do you want to edit another book?(y/n) ");
            fflush(stdin);
            scanf("%c", &another);

            if(another == 'y' || another == 'Y')
                edit_book();

            if(another == 'n' || another == 'N')
                book_menu();

            else{
                printf("\n     Invalid Choice ! ");
                printf("\n     ");
            }

        }
        while(another != 'y' || another != 'Y' || another != 'n' || another != 'N');

    }

}
