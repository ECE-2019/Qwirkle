#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

typedef struct tuile
{
    int posx;
    int posy;
    int color;
    char * form;
    int score;
} Tuile;

typedef struct player
{
    char * pseudo[15];
    int score_game;
    int score_play;
    struct tuile hand[6];

} Player;

typedef struct game
{
    struct player players[5];
    struct tuile pioche[108];
    struct tuile field[12][26];

} Game;


void menu();
void bye_screen();
void game(struct player * players);
void set_coord(int x, int y);
void get_key(int * key);
void logger(char * message, int position);
void player_name(int player_nb);
void player_number();
struct tuile draw_tuile();

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

void set_coord2(int x, int y)
{
    COORD mycoord;
    mycoord.X = x;
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
void logger(char * message, int position){
    set_coord(20,20);
    printf("%s : %d", message, position);
    Sleep(1000);
    set_coord(3,position);
}


void color(int color_text,int color_fond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,color_fond*16+color_text);
    /**
    0: noir
    1: bleu fonc�
    2: vert
    3: bleu-gris
    4: marron
    5: pourpre
    6: kaki
    7: gris clair
    8: gris
    9: bleu
    10: vert fluo
    11: turquoise
    12: rouge
    13: rose fluo
    14: jaune fluo
    15: blanc
    **/
}




void menu()
{
    int key = -1, position = 3;

    system("cls");
    puts("\n***********************MENU***********************\n");
    puts("\tDemarrer une nouvelle partie");
    puts("\tReprendre la partie en cours");
    puts("\tConsulter les scores");
    puts("\tConsulter les options");
    puts("\tQuitter le jeu");
    set_coord(3,position);
    printf(">");
    set_coord(3,position);

    while(key != 0 && key != 1){
        if(kbhit()){
            get_key(&key);
            if(key == 2 && position < 7){
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
            player_number();
            break;
        case 4:
            printf("load_game();");
            break;
        case 5:
            printf("score();");
            break;
        case 6:
            printf("options();");
            break;
        case 7:
            bye_screen();
            break;
        }
    }
}

void player_number(){

    int key = -1, position = 3;

    system("cls");
    printf("\n***********************Choisissez un nombre de joueur (2-4)***********************\n\n\t2\n\t3\n\t4");
    set_coord(3,position);
    printf(">");
    set_coord(3,position);

    while(key != 0 && key != 1){
        if(kbhit()){
            get_key(&key);
            if(key == 2 && position < 5){
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
            player_name(2);
            break;
        case 4:
            player_name(3);
            break;
        case 5:
            player_name(4);
            break;
        }
    }
}

void player_name(int player_nb){
    int i;
    struct player players[player_nb];

    for(i = 0; i < player_nb; i++){
        system("cls");
        printf("\n***********************Pseudo du joueur %d (15 charact)***********************\n>", i+1);
        scanf("%s",players[i].pseudo);
    }
    game(players);

}

void game(struct player * players){

    system("cls");
    puts(" abcdefghijklmopqrstuwxyz\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
        //puts(" a b c d e f g h i j k l m o p q r s t u w x y z\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
    set_coord(15,1);


    int i = 1, j;
    size_t length = sizeof(players[i].hand) / sizeof(players[i].hand[0]);
    printf("Player %d",i);
    set_coord(15,2);
    printf("%s", players[i].pseudo);

    set_coord(15,4);
    puts("Main");
    set_coord(15,5);
    for(j = 0; j < length; j++){
        //draw_tuile();
        players[i].hand[j] = draw_tuile();
        color(players[i].hand[j].color,0);
        printf("%c ", players[i].hand[j].form);
    }
    set_coord(15,6);
    for(j = 0; j < length; j++){
        color(players[i].hand[j].color,0);
        printf("%d ", players[i].hand[j].score);
    }
    color(15,0);

    set_coord(15,8);
    puts("Coup");
    set_coord(15,9);
    //
    set_coord(15,11);
    puts("Score coup");
    set_coord(15,12);
    printf("%d",players[i].score_play);
    set_coord(15,14);
    puts("Score total");
    set_coord(15,15);
    printf("%d",players[i].score_game);
    //set_coord(15,9);

    //print choisissz une tuile
    set_coord(15,5);
    color(0,players[i].hand[0].color);
    printf("%c", players[i].hand[0].form);
    set_coord(15,5);

    int key = -1, position = 15;

    //choose tuile
    while(key != 0 && key != 1){
        if(kbhit()){
            get_key(&key);
            //right
            if(key == 6 && position < 20){
                //inverse les couleurs la position
                set_coord(position,5);
                color(players[i].hand[position-15].color,0);
                printf("%c", players[i].hand[position-15].form);
                //deplacement
                position++;
                set_coord(position,5);
                //inverse les couleurs
                color(0,players[i].hand[position-15].color);
                printf("%c", players[i].hand[position-15].form);
                //reset position
                set_coord(position,5);
            //left
            }else if(key == 4 && position > 15){
                set_coord(position,5);
                color(players[i].hand[position-15].color,0);
                printf("%c", players[i].hand[position-15].form);
                position--;
                set_coord(position,5);
                color(0,players[i].hand[position-15].color);
                printf("%c", players[i].hand[position-15].form);
                set_coord(position,5);
            }

            //moove tuile
            else if(key == 0){
                exit(0);
            }else if(key == 1){
                struct tuile tuile_selected = players[i].hand[position-15];
                struct game game;
                //game.field = {}

                int posx = 10, posy = 10;
                key = -1;
                while(key != 0 && key != 1){
                    //put tuile on field
                    set_coord2(posx,posy);
                    color(tuile_selected.color,0);
                    printf("%c", tuile_selected.form);
                    set_coord2(posx,posy);

                    if(kbhit()){
                        get_key(&key);
                        //right
                        if(key == 6 && posx < 24){
                            set_coord2(posx,posy);
                            printf(" ");
                            posx++;
                            set_coord2(posx,posy);
                            color(tuile_selected.color,0);
                            printf("%c", tuile_selected.form);
                            set_coord2(posx,posy);
                        //left
                        }else if(key == 4 && posx > 1){
                            set_coord2(posx,posy);
                            printf(" ");
                            posx--;
                            set_coord2(posx,posy);
                            color(tuile_selected.color,0);
                            printf("%c", tuile_selected.form);
                            set_coord2(posx,posy);
                        //up
                        }else if(key == 8 && posy > 1){
                            set_coord2(posx,posy);
                            printf(" ");
                            posy--;
                            set_coord2(posx,posy);
                            color(tuile_selected.color,0);
                            printf("%c", tuile_selected.form);
                            set_coord2(posx,posy);
                        //down
                        }else if(key == 2 && posy < 12){
                            set_coord2(posx,posy);
                            printf(" ");
                            posy++;
                            set_coord2(posx,posy);
                            color(tuile_selected.color,0);
                            printf("%c", tuile_selected.form);
                            set_coord2(posx,posy);
                        }
                    }
                }
            }
        }
    }

    while(1){

    }

}

struct tuile draw_tuile(){
    /**
    0: noir
    1: bleu fonc�
    2: vert
    3: bleu-gris
    4: marron
    5: pourpre
    6: kaki
    7: gris clair
    8: gris
    9: bleu
    10: vert fluo
    11: turquoise
    12: rouge
    13: rose fluo
    14: jaune fluo
    15: blanc
    **/
    int form = 6;
    int color = 6;
    int colors[] =  {1,12,2,14,11,8};
    char forms[] =  {0xC8, 0xC9, 0xBB, 0xBC, 0xCA, 0xCB};

    struct tuile tuile1;
    tuile1.form = forms[rand()%form];
    tuile1.color = colors[rand()%color];
    switch(tuile1.color){
        case 1:
            tuile1.score = 1;
            break;
        case 12:
            tuile1.score = 2;
            break;
        case 2:
            tuile1.score = 3;
            break;
        case 14:
            tuile1.score = 4;
            break;
        case 11:
            tuile1.score = 5;
            break;
        case 8:
            tuile1.score = 6;
            break;
    }
    //printf("%c %d",tuile1.form, tuile1.color );
    return tuile1;

}


void bye_screen(){
    system("cls");
    color(11,0);
    puts("\n\n");
    puts("\t  #######     ##    ##    ######## ");
    puts("\t  ##    ##     ##  ##     ##       ");
    puts("\t  ##    ##      ####      ##       ");
    puts("\t  ########       ##       ######## ");
    puts("\t  ##    ##       ##       ##       ");
    puts("\t  ##    ##       ##       ##       ");
    puts("\t  #######        ##       ######## ");
    Sleep(2000);
    color(15,0);
    system("cls");
}
