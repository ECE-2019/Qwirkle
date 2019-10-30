#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

typedef struct tuile
{
  int color;
  int form;
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
  struct tuile field[26][12];
  int mode;
  int nb_player;
} Game;


void menu();
void bye_screen();
void game(struct player * players);
void set_coord(int x, int y);
void get_key(int * key);
void player_name();
void player_number();
struct tuile draw_tuile(struct game * game);
void dialog(char * message);
void moove_tuile(struct game game, int posx, int posy, struct tuile tuile);
void set_score_play(struct player * player, struct tuile tuile);
void log(char * message);
void log_int(int message);

int main()
{
  srand(time(NULL));
  system("chcp 850");
  log("Hello ");
  log_int(123);
  menu();

  return 0;
}

void set_coord(int x, int y)
{
  COORD mycoord;
  mycoord.X = x;
  mycoord.Y = y;
  SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void get_key(int * key){
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
void log(char * message){
  FILE *f;
  f = fopen("qwirkle.log", "a"); // a+ (create + append) option will allow appending which is useful in a log file
  if (f == NULL) { /* Something is wrong   */}
  fprintf(f, message);
  fclose(f);
}
void log_int(int number){
  FILE *f;
  f = fopen("qwirkle.log", "a"); // a+ (create + append) option will allow appending which is useful in a log file
  if (f == NULL) { /* Something is wrong   */}
  char str[10];
  sprintf(str, "%d\n", number);
  fprintf(f, str);
  fclose(f);
}
void set_color(int color_text,int color_fond){
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
void reset_color(){
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H,0*16+15);
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
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 0 && key != 1){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 7){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
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
  log("Hello encore\n");
  get_mode(&game);
  get_player_number(&game);
  get_player_name(&game);
  display_game();
  display_field(&game);
  play(&game);
}

void get_mode(struct game * game){
  int key = -1, position = 3;

  system("cls");
  puts("\n*********************Choisissez un mode*********************\n");
  puts("\t Dégradé (contour)");
  puts("\t Normal");
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 0 && key != 1){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 4){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }

  if(key == 0){
    exit(0);
  }else if(key == 1){
    game->mode = position-2;// 1-2

    int i, j;
    int colors[] =  {1,12,2,14,11,8};
    int scores[] =  {1,2,3,4,5,6};
    int forms[] =  {187, 188, 200, 201, 202, 203, 204, 185, 185, 205, 206};
    for(i = 0; i < 6; i++){
      for(j = 0; j < 6; j++){
        game->pioche[j+6*i].color = colors[i];
        game->pioche[j+6*i].form = forms[j];
        game->pioche[j+6*i].score = scores[i];
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
      //printf("%d-%c -> %d-%c\n",random1,game->pioche[random1].form, random2,game->pioche[random2].form, random2);
    }
    // reset field
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 12; j++) {
        game->field[i][j].score = 0;
        game->field[i][j].form = 0;
        game->field[i][j].color = 0;
      }
    }
  }
}

void get_player_number(struct game * game){
  int position = 3, key = -1;

  system("cls");
  puts("\n************Choisissez un nombre de joueur (2-4)************\n");
  puts("\t 2");
  puts("\t 3");
  puts("\t 4");
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 0 && key != 1){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 5){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }
  if(key == 0){
    exit(0);
  }else if(key == 1){
    // allocation de la memoire pour les struct player de game
    int i,j;
    game->players = calloc(5-position, sizeof(struct player));
    game->nb_player = 5-position;
    for(i = 0; i < game->nb_player; i++){
      for(j = 0; j < 6; j++){
        game->players[i].hand[j] = draw_tuile(game);
        //game->players[i].hand[j].posx = 29+2*j
        //game->players[i].hand[j].posy = 5
      }
    }
  }
}

void get_player_name(struct game * game){
  int i;
  for(i = 0; i < game->nb_player; i++){
    system("cls");
    printf("\n**************Pseudo du joueur %d (15 charact)**************\n", i+1);
    set_coord(7,3);
    printf(">");
    scanf("%s", game->players[i].pseudo);
  }

}

void display_game(){
  system("cls");
  puts(" abcdefghijklmnopqrstuvwxyz\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
  //puts(" a b c d e f g h i j k l m o p q r s t u w x y z\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
  set_coord(30,1);
  printf("player");
  set_coord(30,4);
  puts("Main");
  set_coord(30,8);
  puts("Coup");
  set_coord(30,11);
  puts("Score coup");
  set_coord(30,14);
  puts("Score total");
}

void display_field(struct game * game){
  int i,j;
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 12; j++) {
      set_coord(i+1,j+1);
      set_color(game->field[i][j].color,0);
      printf("%c",game->field[i][j].form);
    }
  }
  reset_color();
}

void display_player_info(struct game * game, int player_nb){
  int j;
  set_coord(37,1);
  printf("%d",player_nb+1);
  set_coord(30,2);
  printf("%s", game->players[player_nb].pseudo);
  set_coord(30,5);
  for(j = 0; j < 6; j++){
    set_color(game->players[player_nb].hand[j].color,0);
    printf("%c ", game->players[player_nb].hand[j].form);
  }
  set_coord(30,6);
  for(j = 0; j < 6; j++){
    set_color(game->players[player_nb].hand[j].color,0);
    printf("%d ", game->players[player_nb].hand[j].score);
  }
  reset_color();
  set_coord(30,9);
  //
  set_coord(30,12);
  printf("%d",game->players[player_nb].score_play);
  set_coord(30,15);
  printf("%d",game->players[player_nb].score_game);
}

void play(struct game * game){
  int i, j, key, position = 30, tuile_nb = 0, n = 0;
  for(i = 0; i < game->nb_player; i++){
  // Debut tour joueur
    display_player_info(game, i);

    dialog("Combien de tuile ?");
    set_coord(20,14);
    while(!(tuile_nb == 49 || tuile_nb == 50 || tuile_nb == 51)){
      tuile_nb = getch();
    }

    for(j = 0; j < tuile_nb - 48; j++){
      display_player_info(game, i);
      char str[34];
      sprintf(str, "Choose a tuile (%d left)", tuile_nb-48-j);
      dialog(str);

      // Select tuile
      set_coord(30,5);
      set_color(0,game->players[i].hand[n].color);
      printf("%c", game->players[i].hand[n].form);
      set_coord(30,5);

      key = -1;
      while(key != 1){
        while(key != 0 && key != 1){
          if(kbhit()){
            get_key(&key);
            log_int(n);
            //right
            if(key == 6 && position < 40){
              set_coord(position,5);
              set_color(game->players[i].hand[n].color,0);
              printf("%c", game->players[i].hand[n].form);
              position = position+2;
              n++;
              set_coord(position,5);
              set_color(0,game->players[i].hand[n].color);
              printf("%c", game->players[i].hand[n].form);
              set_coord(position,5);
              //left
            }else if(key == 4 && position > 30){
              set_coord(position,5);
              set_color(game->players[i].hand[n].color,0);
              printf("%c", game->players[i].hand[n].form);
              position = position-2;
              n--;
              set_coord(position,5);
              set_color(0,game->players[i].hand[n].color);
              printf("%c", game->players[i].hand[n].form);
              set_coord(position,5);
            }else if(key == 1){
              //Place la tuile sur le field
              reset_color();
              key = set_tuile(game, i, n);
            }
          }
        }
        //color(15,0);
      }
    }
    // Fin du tour du joueur
  }
}

//Place la tuile sur le field
int set_tuile(struct game * game, int player_nb, int tuile_nb){
  log_int(tuile_nb);
  struct tuile tuile = game->players[player_nb].hand[tuile_nb];
  int posx, posy, new_posx, new_posy, key = -1;
  posx = posy = new_posx = new_posy = 10;

  //game->player[player_nb].hand[position];

  dialog("Placez la tuile:");
  //put tuile on field
  set_coord(posx,posy);
  set_color(tuile.color,0);
  printf("%c", tuile.form);
  set_score_play(&game->players[player_nb], tuile);
  set_coord(posx,posy);

  while(key != 0 && key != 1){
    if(kbhit()){
      get_key(&key);
      //right
      if(key == 6 && posx < 26){
        new_posx = posx+1;
        //left
      }else if(key == 4 && posx > 1){
        new_posx = posx-1;
        //up
      }else if(key == 8 && posy > 1){
        new_posy = posy-1;
        //down
      }else if(key == 2 && posy < 12){
        new_posy = posy+1;
      }

      // si la position a change
      if (new_posx != posx || new_posy != posy ) {
        display_field(game);
        set_coord(new_posx,new_posy);
        set_color(tuile.color, 0);
        printf("%c", tuile.form);
        posx = new_posx;
        posy = new_posy;
      }
      set_score_play(&game->players[player_nb], tuile);
      set_coord(posx,posy);
    }
  }
  if(key == 0){
    display_field(&game);
  }else if(key == 1){
    game->field[posx-1][posy-1] = tuile;
    game->players[player_nb].hand[tuile_nb] = draw_tuile(game);

    char * str;
    sprintf(&str, "posx %d posy %d\n", posx, posy);
    log("pos tuile");
    log(&str);
    //Sleep(10000);


    // remove tuile from hand
    //game->players[player_nb].hand[position] = ;
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
  set_coord(30,12);
  printf("%d   ",player->score_play);
}



void dialog(char * message){
  set_coord(1,14);
  printf("%s       ", message);
}

struct tuile draw_tuile(struct game * game){
  struct tuile tuile;
  int i, pioche_length = 0;

  if(game->mode == 1){
    pioche_length = 36;
  }else if(game->mode == 2){
    pioche_length = 108;
  }

  for(i = pioche_length-1; i >= 0; i--){
    if(game->pioche[i].score == 0){
      continue;
    }
    tuile = game->pioche[i];
    game->pioche[i].score = 0;
    break;
    /*if(game->pioche[i].score > 0){
    tuile = game->pioche[i]
    game.pioche[i].score = 0;
    break;
  }*/
}
return tuile;
}

void bye_screen(){
  system("cls");
  set_color(11,0);
  puts("\n\n");
  puts("\t  #######     ##    ##    ######## ");
  puts("\t  ##    ##     ##  ##     ##       ");
  puts("\t  ##    ##      ####      ##       ");
  puts("\t  ########       ##       ######## ");
  puts("\t  ##    ##       ##       ##       ");
  puts("\t  ##    ##       ##       ##       ");
  puts("\t  #######        ##       ######## ");
  Sleep(2000);
  reset_color();
  system("cls");
}
