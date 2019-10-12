#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

void menu();
void set_coord(int x, int y);
void get_key(int * key);
void logger(char * message, int position);

int main()
{
    srand(time(NULL));
    menu();

    return 0;
}

void set_coord(int x, int y)
{
    COORD mycoord;
    mycoord.X = 2*x;
    mycoord.Y = y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void get_key(int * key)
{
    int input = getch();
    //printf("%d",input);
    switch(input){
    case 72:
    case 122:
    case 56:
        //printf("up");
        *key = 8;
        break;
    case 75:
    case 113:
    case 52:
        //printf("left");
        *key = 4;
        break;
    case 77:
    case 100:
    case 54:
        //printf("right");
        *key = 6;
        break;
    case 80:
    case 115:
    case 50:
        //printf("down");
        *key = 2;
        break;
    case 13:
        //printf("enter");
        *key = 1;
        break;
    case 27:
        //printf("esc");
        *key = 0;
        break;
    }
}

void menu()
{
    int key = -1, position = 3;

    system("cls");
    printf("\n***********************MENU***********************\n\n\tDemarrer une nouvelle partie\n\tReprendre la partie en cours\n\tConsulter les options\n\tQuitter le jeu");
    set_coord(3,position);
    printf(">");
    set_coord(3,position);

    while(key != 0 && key != 1)
    {
        if(kbhit())
        {
            get_key(&key);
            if(key == 2 && position < 6){
                set_coord(3,position);
                printf(" ");
                position++;
                set_coord(3,position);
                printf(">");
                set_coord(3,position);
            }else if(key == 8 && position > 3){
                set_coord(3,position);
                printf(" ");
                position--;
                set_coord(3,position);
                printf(">");
                set_coord(3,position);
            }
        }
    }

    if(key == 0){
        exit(0);
    }else if(key == 1){
        switch(position){
        case 3:
            printf("new_game();");
            break;
        case 4:
            printf("load_game();");
            break;
        case 5:
            printf("options();");
            break;
        case 6:
            printf("bye");
            break;
        }
    }
}

void logger(char * message, int position){
    set_coord(20,20);
    printf("%s : %d", message, position);
    set_coord(3,position);
}
