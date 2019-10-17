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
} tuile;

typedef struct player
{
    char pseudo[15];
    int score_game;
    int score_play;
    struct tuile hand[6];
} player;

typedef struct game
{
    struct player * players;
    struct tuile pioche[108];
    struct tuile field[12][26];
    int mode;
    int nb_player;
} Game;


void menu();
void bye_screen();
void game(struct player * players);
void set_coord(int x, int y);
void get_key(int * key);
void logger(char * message, int position);
void player_name();
void player_number();
struct tuile draw_tuile();
void dialog(char * message, int posx, int posy);
void moove_tuile(int posx, int posy, struct tuile tuile);
void set_score_play(struct player * player, struct tuile tuile);

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


void menu(){
    int key = -1, position = 3;

    system("cls");
    puts("\n***********************MENU***********************\n");
    puts("\t Demarrer une nouvelle partie");
    puts("\t Reprendre la partie en cours");
    puts("\t Consulter les scores");
    puts("\t Consulter les options");
    puts("\t Quitter le jeu");
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
            new_game();
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

void new_game(){

    struct game game;
    int i;

    get_mode(&game);
    get_player_number(&game);
    get_player_name(&game);
    display_game();

    for(i = 0; i < game.nb_player; i++){
        display_player_info(&game.players[i], i);
        play(&game, i);
    }

}

void get_mode(struct game * game){
    int key = -1, position = 3;

    system("cls");
    puts("\n*********************Choisissez un mode*********************\n");
    puts("\t Dégradé (contour)");
    puts("\t Normal");
    set_coord(3,position);
    printf(">");
    set_coord(3,position);

    while(key != 0 && key != 1){
        if(kbhit()){
            get_key(&key);
            if(key == 2 && position < 4){
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
        game->mode = 5-position;// 1-2
        int i, j;
        int colors[] =  {1,12,2,14,11,8};
        char forms[] =  {0xC9, 0xC8, 0xBB, 0xBC, 0xCB, 0xCA};
        for(i = 0; i < 6; i++){
            for(j = 0; j < 6; j++){
                game->pioche[j+6*i].posx = -1;
                game->pioche[j+6*i].posy = -1;
                game->pioche[j+6*i].color = colors[i];
                game->pioche[j+6*i].form = forms[j];
            }
        }
        //shuffle it
        struct tuile buf;
        int k, random1, random2, n =35;
        for(k = 0; k < n; k++){
            random1 = rand()%n;
            random2 = rand()%n;
            //printf("%d-%c -> %d-%c\n",random1,game->pioche[random1].form, random2,game->pioche[random2].form);
            buf = game->pioche[random1];
            game->pioche[random1] = game->pioche[random2];
            game->pioche[random2] = buf;
            //printf("%d-%c -> %d-%c\n",random1,game->pioche[random1].form, random2,game->pioche[random2].form);
        }

    }

}

void get_player_number(struct game * game){

    int position = 3, key = -1;

    system("cls");
    puts("\n*********************Choisissez un nombre de joueur (2-4)*********************\n");
    puts("\t 2");
    puts("\t 3");
    puts("\t 4");
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
        // allocation de la memoire pour les struct player
        int i,j;
        game->players = calloc(5-position, sizeof(struct player));
        game->nb_player = 5-position;
        for(i = 0; i < game->nb_player; i++){
            for(j = 0; j < 6; j++){
                game->players[i].hand[j] = draw_tuile();
            }
        }
    }
}

void get_player_name(struct game * game){
    int i;
    for(i = 0; i < game->nb_player; i++){
        system("cls");
        printf("\n***********************Pseudo du joueur %d (15 charact)***********************\n", i+1);
        set_coord(3,3);
        printf(">");
        scanf("%s", game->players[i].pseudo);
    }

}

void display_game(){
    system("cls");
    puts(" abcdefghijklmopqrstuwxyz\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
    //puts(" a b c d e f g h i j k l m o p q r s t u w x y z\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
    set_coord(15,1);
    printf("player");
    set_coord(15,4);
    puts("Main");
    set_coord(15,8);
    puts("Coup");
    set_coord(15,11);
    puts("Score coup");
    set_coord(15,14);
    puts("Score total");
}

void display_player_info(struct player * player, int player_nb){
    int j;
    set_coord2(37,1);
    printf("%d",player_nb+1);
    set_coord(15,2);
    printf("%s", player->pseudo);
    set_coord(15,5);
    for(j = 0; j < 6; j++){
        //draw_tuile();
        player->hand[j] = draw_tuile();
        color(player->hand[j].color,0);
        printf("%c ", player->hand[j].form);
    }
    set_coord(15,6);
    for(j = 0; j < 6; j++){
        color(player->hand[j].color,0);
        printf("%d ", player->hand[j].score);
    }
    color(15,0);
    set_coord(15,9);
    //
    set_coord(15,12);
    printf("%d",player->score_play);
    set_coord(15,15);
    printf("%d",player->score_game);
}

void play(struct game * game, int player_nb){
    int i, key, position = 15, tuile_nb = 0;

    dialog("Combien de tuile ?", 10, 14);

    while(!(tuile_nb == 49 || tuile_nb == 50 || tuile_nb == 51)){
        tuile_nb = getch();
    }

    for(i = 0; i < tuile_nb - 48; i++){
        char str[34];
        sprintf(str, "Choisissez une tuile (encore %d)", tuile_nb-48-i);
        dialog(str, 15, 5);
        key = -1;
        // color reverse first tuile
        while(key != 1){
            while(key != 0 && key != 1){
                if(kbhit()){
                    get_key(&key);
                    //right
                    if(key == 6 && position < 20){
                        set_coord(position,5);
                        color(game->players[player_nb].hand[position-15].color,0);
                        printf("%c", game->players[player_nb].hand[position-15].form);
                        position++;
                        set_coord(position,5);
                        color(0,game->players[player_nb].hand[position-15].color);
                        printf("%c", game->players[player_nb].hand[position-15].form);
                        set_coord(position,5);
                    //left
                    }else if(key == 4 && position > 15){
                        set_coord(position,5);
                        color(game->players[player_nb].hand[position-15].color,0);
                        printf("%c", game->players[player_nb].hand[position-15].form);
                        position--;
                        set_coord(position,5);
                        color(0,game->players[player_nb].hand[position-15].color);
                        printf("%c", game->players[player_nb].hand[position-15].form);
                        set_coord(position,5);
                    }else if(key == 1){
                        key = set_tuile(game->players[player_nb], position);
                    }
                }
            }
            color(15,0);
        }
    }
    //fin du tour du joueur
}

int set_tuile(struct player player, int position){
    struct tuile tuile_selected = player.hand[position-15];
    struct game game;
    int posx = 10, posy = 10, key = -1;

    dialog("Placez une tuile:", posx, posy);

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
                moove_tuile(posx, posy, tuile_selected);
                set_score_play(&player, tuile_selected);
            //left
            }else if(key == 4 && posx > 1){
                set_coord2(posx,posy);
                printf(" ");
                posx--;
                moove_tuile(posx, posy, tuile_selected);
                set_score_play(&player, tuile_selected);
            //up
            }else if(key == 8 && posy > 1){
                set_coord2(posx,posy);
                printf(" ");
                posy--;
                moove_tuile(posx, posy, tuile_selected);
                set_score_play(&player, tuile_selected);
            //down
            }else if(key == 2 && posy < 12){
                set_coord2(posx,posy);
                printf(" ");
                posy++;
                moove_tuile(posx, posy, tuile_selected);
                set_score_play(&player, tuile_selected);
            }
        }
    }
    if(key == 0){
        set_coord2(posx,posy);
        printf(" "); //remove tuile and put older one
    }
    return key;

}

int get_score_play(struct tuile tuile){
    int score_play = 0;
    score_play = tuile.score;

    return score_play;
}

void set_score_play(struct player * player, struct tuile tuile){
    player->score_play = get_score_play(tuile);
    set_coord(15,12);
    printf("%d   ",player->score_play);
}

void moove_tuile(int posx, int posy, struct tuile tuile){
    set_coord2(posx,posy);
    color(tuile.color,0);
    printf("%c", tuile.form);
    color(15,0);
    set_coord2(posx,posy);
}

void dialog(char * message, int posx, int posy){
    set_coord(1,14);
    printf("%s        ", message);
    set_coord(posx, posy);
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

    struct tuile tuile;
    tuile.form = forms[rand()%form];
    tuile.color = colors[rand()%color];
    switch(tuile.color){
        case 1:
            tuile.score = 1;
            break;
        case 12:
            tuile.score = 2;
            break;
        case 2:
            tuile.score = 3;
            break;
        case 14:
            tuile.score = 4;
            break;
        case 11:
            tuile.score = 5;
            break;
        case 8:
            tuile.score = 6;
            break;
    }
    //printf("%c %d",tuile1.form, tuile1.color );
    return tuile;
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
