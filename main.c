#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "frequent_function.h"

void library_menu(void);

int main()
{

    library_menu();

    return 0;
}


void library_menu(void){

    int choice = 0;

    system("cls");

    gotoxy(5,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  LIBRARY MANAGEMENT SYSTEM  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5,8);
    printf("\xDB\xDB\xDB 1. BOOK MENU");
    gotoxy(5,10);
    printf("\xDB\xDB\xDB 2. ISSUE MENU");
    gotoxy(5,12);
    printf("\xDB\xDB\xDB 3. RETURN MENU");
    gotoxy(5,14);
    printf("\xDB\xDB\xDB 4. EXIT");
    gotoxy(5,17);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5,20);
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);


    switch(choice){
    case 1:
        book_menu();
        break;

    case 2:
      //  issue_menu();
        break;

    case 3:
     //   return_menu();
        break;

    case 4:
        exit(0);

    default:
        printf("INVALID CHOICE !");
        break;
    }

    return 0;
}
