#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

void menu();
void gotoligcol(int x, int y);
void get_key(int * key);
void logger(char * message, int position);

int main()
{
    //printf("Hello world!\n");
    menu();
    srand(time(NULL));
    return 0;
}

void gotoligcol(int x, int y)
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
            case 27:
                //printf("esc");
                *key = 0;
                break;
            }
}

void menu()
{
    int choice = 0,i;
    int key = 1;
    int position = 3;
    printf("\n***********************MENU***********************\n\n\tDemarrer une nouvelle partie\n\tReprendre la partie en cours\n\tConsulter les options\n\tQuitter le jeu");
    gotoligcol(3,position);
    printf(">");
    while(key != 0)
    {
        //while (kbhit())
        //{
            //printf("hited");
            //Sleep(500);
            //logger("Hited", position);
            get_key(&key);
            if(key == 2 && position < 6){
                gotoligcol(3,position);
                printf(" ");
                position++;
                gotoligcol(3,position);
                printf(">");
                gotoligcol(3,position);

            }else if(key == 8 && position > 3){
                gotoligcol(3,position);
                printf(" ");
                position--;
                gotoligcol(3,position);
                printf(">");
                gotoligcol(3,position);
            }
        //}
    //printf("%d", key);
    }
}

void logger(char * message, int position){
    gotoligcol(20,20);
    printf("%s : %d", message, position);
    gotoligcol(3,position);
}
