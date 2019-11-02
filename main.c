#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#include "struct.h"
#include "prototype.h"


void menu();
void new_game();
void get_mode(game * gane);
void get_player_name(game * gane);
void get_player_number(game * gane);
void display_game();
void display_player_info(game * game, int player_nb);
void display_field(game * game);
void play(game * game);
int set_tuile(game * game, int player_nb, int tuile_nb);
void moove_tuile(game game, int posx, int posy, tuile tuile);
void set_score_play(player * player, tuile * tuile);

void dialog(char * message);
void bye_screen();

tuile * draw_tuile(game * game);



int main()
{
  srand(time(NULL));
  system("chcp 850");
  log_char("[OK] Test log()\n");
  log_int(0);
  menu();

  return 0;
}

void menu()
{
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
void new_game()
{
  game game;
  get_mode(&game);
  get_player_number(&game);
  get_player_name(&game);
  display_game();
  display_field(&game);
  play(&game);
}

void get_mode(game * game)
{
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
    tuile * tuile = NULL;
    int i, j;
    int colors[] =  {1,12,2,14,11,8};
    int scores[] =  {1,2,3,4,5,6};
    int forms[] =  {187, 188, 200, 201, 202, 203, 204, 185, 185, 205, 206};

    for(i = 0; i < 6; i++){
      for(j = 0; j < 6; j++){
        tuile = new_struct(colors[i], forms[j], scores[i]);
        game->pioche = push_link(game->pioche, tuile);
      }
    }
    print_list(game->pioche);
    // //shuffle it
    // struct tuile buf;
    // int k, random1, random2, n =35;
    // for(k = 0; k < n; k++){
    //   random1 = rand()%n;
    //   random2 = rand()%n;
    //   //printf("%d-%c -> %d-%c\n",random1,game->pioche[random1].form, random2,game->pioche[random2].form);
    //   buf = game->pioche[random1];
    //   game->pioche[random1] = game->pioche[random2];
    //   game->pioche[random2] = buf;
    //   //printf("%d-%c -> %d-%c\n",random1,game->pioche[random1].form, random2,game->pioche[random2].form, random2);
    // }
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

void get_player_number(game * game)
{
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
    game->players = calloc(5-position, sizeof(struct Player));
    game->nb_player = 5-position;
    for(i = 0; i < game->nb_player; i++){
      for(j = 0; j < 6; j++){
        game->players[i].hand = push_link(game->players[i].hand, draw_tuile(game));
      }
      //print_list(game->players[i].hand);
    }
  }
}

void get_player_name(game * game)
{
  int i;
  for(i = 0; i < game->nb_player; i++){
    system("cls");
    printf("\n**************Pseudo du joueur %d (15 charact)**************\n", i+1);
    set_coord(7,3);
    printf(">");
    scanf("%s", game->players[i].pseudo);
  }

}

void display_game()
{
  system("cls");
  puts(" abcdefghijklmnopqrstuvwxyz\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
  //puts(" a b c d e f g h i j k l m o p q r s t u w x y z\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
  set_coord(30,1);
  printf("Player");
  set_coord(30,4);
  puts("Hand");
  set_coord(30,8);
  puts("Score play");
  set_coord(30,11);
  puts("Score game");
}

void display_field(game * game)
{
  int i,j;
  for (i = 0; i < 26; i++) {
    for (j = 0; j < 12; j++) {
      set_coord(i+1,j+1);
      set_color(game->field[i][j].color,0);
      printf("%c",game->field[i][j].form);
    }
  }
  reset_color();
}

void display_player_info(game * game, int player_nb)
{
  int j;
  tuile * tuile;
  int size_l = list_length(game->players[player_nb].hand);

  set_coord(37,1);
  printf("%d",player_nb+1);
  set_coord(30,2);
  printf("%s", game->players[player_nb].pseudo);
  for(j = 0; j < size_l; j++){
    tuile = get_link_at(game->players[player_nb].hand,j);
    set_coord(30+j*2,5);
    set_color(tuile->color,0);
    printf("%c ", tuile->form);
    set_coord(30+j*2,6);
    set_color(tuile->color,0);
    printf("%d ", tuile->score);
  }
  reset_color();
  set_coord(30,9);
  printf("%d  ",game->players[player_nb].score_play);
  set_coord(30,12);
  printf("%d  ",game->players[player_nb].score_game);
}

void play(game * game)
{
  int i, j, key, tuile_nb, n, position, size_l;
  tuile * tuile;

  for(i = 0; i < game->nb_player; i++){
  // Debut tour joueur
    tuile_nb = 0;
    game->players[i].score_play = 0;
    display_player_info(game, i);

    dialog("How many de tile ?");
    set_coord(20,14);
    while(!(tuile_nb == 49 || tuile_nb == 50 || tuile_nb == 51)){
      tuile_nb = getch();
    }

    for(j = 0; j < tuile_nb - 48; j++){
      n = 0;
      key = -1;
      position = 30;
      size_l = list_length(game->players[i].hand);
      reset_color();
      display_player_info(game, i);

      // Dialog
      char str[34];
      sprintf(str, "Choose a tile (%d left)", tuile_nb-48-j);
      dialog(str);

      // Select first tuile
      tuile = get_link_at(game->players[i].hand, 0);
      set_coord(30,5);
      set_color(0,tuile->color);
      printf("%c", tuile->form);
      set_coord(30,5);

      while(key != 1){
        while(key != 0 && key != 1){
          if(kbhit()){
            get_key(&key);
            //right
            if(key == 6 && position < 30+(size_l*2-2)){
              set_coord(position,5);

              tuile = get_link_at(game->players[i].hand, n);
              set_color(tuile->color,0);
              printf("%c", tuile->form);

              position = position+2;
              n++;
              set_coord(position,5);

              tuile = get_link_at(game->players[i].hand, n);
              set_color(0,tuile->color);
              printf("%c", tuile->form);
              set_coord(position,5);
              //left
            }else if(key == 4 && position > 30){
              set_coord(position,5);

              tuile = get_link_at(game->players[i].hand, n);
              set_color(tuile->color,0);
              printf("%c", tuile->form);

              position = position-2;
              n--;
              set_coord(position,5);
              tuile = get_link_at(game->players[i].hand, n);
              set_color(0,tuile->color);
              printf("%c", tuile->form);
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
    game->players[i].score_game += game->players[i].score_play;
    display_player_info(game, i);
  }
}

//Place la tuile sur le field
int set_tuile(game * game, int player_nb, int tuile_nb){
  log_int(tuile_nb);
  tuile * tuile = get_link_at(game->players[player_nb].hand, tuile_nb);
  int posx, posy, new_posx, new_posy, key = -1;
  posx = posy = new_posx = new_posy = 10;

  //game->player[player_nb].hand[position];

  dialog("Placez la tuile:");
  //put tuile on field
  set_coord(posx,posy);
  set_color(tuile->color,0);
  printf("%c", tuile->form);
  reset_color();
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
        set_color(tuile->color, 0);
        printf("%c", tuile->form);
        reset_color();
        posx = new_posx;
        posy = new_posy;
      }
      //set_score_play(&game->players[player_nb], tuile);
      set_coord(posx,posy);
    }
  }
  if(key == 0){
    display_field(game);
  }else if(key == 1){
    // pose la tuile su le field
    game->field[posx-1][posy-1] = *tuile;
    // store la tuile dans la temp hand
    //game->players[player_nb].temp_hand[tuile_nb] = *tuile;
    // reset tuile hand
    remove_link_at(game->players[player_nb].hand, tuile_nb);
    //
    // tire une nouvellle tuile de la pioche
    //tuile = draw_tuile(game);

  }else{
    // fin de partie
    // end_game()
    log_char("end game");
    exit(0);
  }
  return key;
}

int get_score_play(tuile * tuile){
  int score_play = 0;
  score_play = tuile->score;
  return score_play;
}
//
void set_score_play(player * player, tuile * tuile){
  player->score_play += get_score_play(tuile);
  set_coord(30,12);
  printf("%d   ",player->score_play);
}

//void set_score_game(struct player * player, )

void dialog(char * message){
  set_coord(1,14);
  printf("%s       ", message);
}

tuile * draw_tuile(game * game){
  log_char("draw_tuile()\n");
  tuile * tuile = get_link_at(game->pioche, list_length(game->pioche)-1);
  game->pioche = remove_link_at(game->pioche, list_length(game->pioche)-1);
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
