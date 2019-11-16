#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#include "struct.h"
#include "display.h"
#include "prototype.h"
#include "tools.h"
/*
  - Dans select_mode shuffle le deck
  - Bloquer la saisie horizon/vertical
  - Bloquer la saisie au milieu de null part
  - changer ses tuiles
  - terminer ou passer
  - free les mooves
*/
void menu();
void new_game();

bool init_game(game * game);
bool select_mode(game * gane);
void input_player_name(game * gane);
bool select_player_number(game * gane);

void play(game * game);
bool set_tuile(game * game, int player_nb, int tuile_nb);
void link_tuile(int posx, int posy, tuile * tuile, game * game);
bool collider(int posx, int posy, tuile * tuile, game * game);
int scorer(int posx, int posy, game * game);
bool was_played (char * play, game * game);
void select_tuile(game * game, int tile_left, int player_nb);

void init_field(game * game);
void shuffle_list(list * deck);
tuile * draw_tuile(game * game);

void dialog(char * message);
void update_hud(game * game, int player_nb);

int main()
{
  srand(time(NULL));
  system("chcp 850");
  log_char("[OK] Test log_char() : a\n");
  log_char("[OK] Test log_int() : ");
  log_int(0);
  display_welcome();
  //system("start prince_loop.wav");
  menu();

  return 0;
}
void menu()
{
  int key = -1, position = 3;

  display_menu();
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 0){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 7){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }else if(key == 0){
        display_bye();
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
          display_options();
          break;
          case 7:
          display_bye();
          break;
        }
      }
      display_menu();
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }
}

void new_game()
{
  game game;
  if(init_game(&game)){
    display_hud();
    display_field(&game);
    play(&game);
    //end_game(&game);
  }
}

void ask_save()
{
  int key = -1, position = 3;

  display_ask_save();
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 1 && key != 0){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 4){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }else if(key == 1){
        switch(position){
          case 3:
          save();
          break;
          case 4:
          display_bye();
          exit(0);
          break;
        }
      }
      display_ask_save();
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }
}

bool quit()
{
  int key = -1, position = 3;

  display_quit();
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 1){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 4){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }else if(key == 1){
        switch(position){
          case 3:
          save();
          case 4:
          display_bye();
          exit(0);
        }
      }else if(key == 0){
        return false;
      }
      display_quit();
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }
  return true;
}

void save()
{

}
bool init_game(game * game)
{
  game->moves = NULL;
  game->deck = NULL;
  if(select_mode(game)){
    if (select_player_number(game)) {
      input_player_name(game);
      init_field(game);
      return true;
    }
  }
  return false;
}

bool select_mode(game * game)
{
  int key = -1, position = 3;

  display_select_mode();
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 1){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 4){
        position++;
      }else if(key == 8 && position > 3){
        position--;
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
            game->deck = push_link(game->deck, tuile);
          }
        }
        shuffle_list(game->deck);
      }else if(key == 0){
        return false;
      }

      display_select_mode();
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }
  return true;
}

bool select_player_number(game * game)
{
  int position = 3, key = -1;

  display_select_player_number();
  set_coord(7,position);
  printf(">");
  set_coord(7,position);

  while(key != 1){
    if(kbhit()){
      get_key(&key);
      set_coord(7,position);
      printf(" ");
      if(key == 2 && position < 5){
        position++;
      }else if(key == 8 && position > 3){
        position--;
      }else if(key == 1){
        // allocation de la memoire pour les struct player de game
        int i,j;
        game->players = calloc(position-1, sizeof(struct Player));
        game->nb_player = position-1;

        for(i = 0; i < game->nb_player; i++){
          for(j = 0; j < 6; j++){
            game->players[i].hand = push_link(game->players[i].hand, draw_tuile(game));
          }
        }
      }else if(key == 0){
        return false;
      }

      display_select_player_number();
      set_coord(7,position);
      printf(">");
      set_coord(7,position);
    }
  }
  return true;
}

void init_field(game * game)
{
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 12; j++) {
      game->field[i][j].score = 0;
      game->field[i][j].form = 0;
      game->field[i][j].color = 0;
      game->field[i][j].posx = 0;
      game->field[i][j].posy = 0;
      game->field[i][j].next_color = NULL;
      game->field[i][j].prev_color = NULL;
      game->field[i][j].next_form = NULL;
      game->field[i][j].prev_form = NULL;
    }
  }
}

void input_player_name(game * game)
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

void update_hud(game * game, int player_nb)
{
  int j;
  tuile * tuile;
  int size_l = list_length(game->players[player_nb].hand);
  set_coord(37,1);
  printf("%d",player_nb+1);
  set_coord(30,2);
  printf("%s", game->players[player_nb].pseudo);
  // clean old plyaer info
  set_coord(30,5);
  printf("            ");
  set_coord(30,6);
  printf("            ");
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
  int i, j, key, tuile_nb, position, exit;
  tuile * drawed_tuile;

  exit = 0;
  while (exit != 1) {
    for(i = 0; i < game->nb_player; i++){
      // Debut tour joueur
      game->players[i].score_play = 0;
      update_hud(game, i);

      // play or exchange
      set_coord(1,14);
      printf("  Place tile    Change hand");
      position = 1;
      set_coord(position,14);
      printf(">");
      set_coord(position,14);

      while(key != 1){
        if(kbhit()){
          get_key(&key);
          if (key == 4 && position == 15) {
            set_coord(position,14);
            printf(" ");
            position = 1;
          }else if(key == 6 && position == 1){
            set_coord(position,14);
            printf(" ");
            position = 15;
          }
          set_coord(position,14);
          printf(">");
          set_coord(position,14);
        }
      }

      if (position == 1) {
        // PLace tite
        dialog("How many tiles ?");
        set_coord(20,14);
        tuile_nb = 0;
        while(tuile_nb < 49 || tuile_nb > 54 ){
          tuile_nb = getch();
        }

        for(j = 0; j < tuile_nb - 48; j++){
          update_hud(game, i);
          select_tuile(game, tuile_nb - 48-j, i);
        }

        free_moves(game);
        game->players[i].score_game += game->players[i].score_play;

        for(j = 0; j < tuile_nb - 48; j++){
          drawed_tuile = draw_tuile(game);
          if (drawed_tuile) {
            push_link(game->players[i].hand, drawed_tuile);
          }else{
            dialog("The deck is empty !");
            exit = 1; // fin du jeu
            break;
          }
        }
      }else if(position == 15){
        // Change hande
        // push back hande in deck
        // pop deck in hand
      }
      update_hud(game, i);
      Sleep(1000);
    }
  }
}

void select_tuile(game * game, int tile_left, int player_nb)
{
  int n, key, position, size_l;
  tuile * selected_tuile;
  // reset_color();
  // Dialog
  char str[34];
  sprintf(str, "Choose a tile (%d left)", tile_left);
  dialog(str);
  // Highlight first tuile
  selected_tuile = get_link_at(game->players[player_nb].hand, 0);
  set_coord(30,5);
  set_color(0,selected_tuile->color);
  printf("%c", selected_tuile->form);
  set_coord(30,5);

  n = 0;
  key = -1;
  position = 30;
  size_l = list_length(game->players[player_nb].hand);
  while(key != 1){
    if(kbhit()){
      get_key(&key);
      //right
      if(key == 6 && position < 30+(size_l*2-2)){
        set_coord(position,5);

        selected_tuile = get_link_at(game->players[player_nb].hand, n);
        set_color(selected_tuile->color,0);
        printf("%c", selected_tuile->form);

        position = position+2;
        n++;
        set_coord(position,5);

        selected_tuile = get_link_at(game->players[player_nb].hand, n);
        set_color(0,selected_tuile->color);
        printf("%c", selected_tuile->form);
        reset_color();
        set_coord(position,5);
        //left
      }else if(key == 4 && position > 30){
        set_coord(position,5);

        selected_tuile = get_link_at(game->players[player_nb].hand, n);
        set_color(selected_tuile->color,0);
        printf("%c", selected_tuile->form);

        position = position-2;
        n--;
        set_coord(position,5);
        selected_tuile = get_link_at(game->players[player_nb].hand, n);
        set_color(0,selected_tuile->color);
        printf("%c", selected_tuile->form);
        reset_color();
        set_coord(position,5);
      }else if(key == 1){
        //Place la tuile sur le field
        if (!set_tuile(game, player_nb, n)) {
          /* saisie avorte retourne a la seletion */
        }
      }else if(key == 0){
        if(quit()){

        }
      }
    }
  }
}

bool set_tuile(game * game, int player_nb, int tuile_nb)
{
  tuile * tuile;
  int posx, posy, new_posx, new_posy, key;

  key  = -1;
  posx = new_posx = 13;
  posy = new_posy = 6;
  tuile = get_link_at(game->players[player_nb].hand, tuile_nb);

  dialog("Place your tile:");
  //put tuile on field
  set_coord(posx,posy);
  set_color(tuile->color,0);
  printf("%c", tuile->form);
  reset_color();
  set_coord(posx,posy);

  while(key != 1){
    if(kbhit()){
      dialog("Place your tile:");
      get_key(&key);
      if(key == 6 && posx < 26){
        new_posx = posx+1;
      }else if(key == 4 && posx > 1){
        new_posx = posx-1;
      }else if(key == 8 && posy > 1){
        new_posy = posy-1;
      }else if(key == 2 && posy < 12){
        new_posy = posy+1;
      }else if(key == 1){// pose la tuile su le field
        if (collider(posx-1,posy-1,tuile, game)) {
          // link la ou les tuiles proches
          link_tuile(posx-1,posy-1,tuile, game);
          if (tuile->next_color || tuile->prev_color || tuile->next_color || tuile->prev_form) {
            // si la tuile a bien ete linke
            log_char("tuiles linked\n");
          }
          tuile->posx = posx;
          tuile->posy = posy;
          // Pose la tuile sur le terrain
          game->field[posx-1][posy-1] = *tuile;
          // Remove tile from hand
          game->players[player_nb].hand = remove_link_at(game->players[player_nb].hand, tuile_nb);
          // Calcul the score
          game->players[player_nb].score_play += scorer(posx-1,posy-1, game);
        }else if(key == 0){
          return false;
        }
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
      set_coord(posx,posy);
    }
  }
  return true;
}

bool collider(int posx, int posy, tuile * tuile, game * game)
{
  struct Tuile side_tuile;
  int i;
  bool col_color,col_form, lig_color,lig_form;

  if (posx < 26 && posx > 0 && posy > 0 && posy < 12){ // If in the field
    if (game->field[posx][posy].score == 0) {// If free space
      col_color = col_form = lig_color = lig_form = false;
      i = 1;
      while (game->field[posx][posy-i].score > 0) {// if tuile
        side_tuile = game->field[posx][posy-i];
        if (side_tuile.color == tuile->color && !col_form) {// if same color and not same form before
          col_color = true;
        }else if (side_tuile.form == tuile->form && !col_color) {// if same form and not same color before
          col_form = true;
        }else {
          if (!col_color && !col_form) {
            dialog("Up tile color and form doesn't match your tile");
          }else if (side_tuile.color == tuile->color && col_form) {
            dialog("Up tile color match but it's form line");
          }else if (side_tuile.form == tuile->form && col_color) {
            dialog("Up tile form match but it's a color line");
          }else{
            dialog("There's a mistake here");
          }
          return false;
        }
        i++;
      }
      i = 1;
      while (game->field[posx][posy+i].score > 0) {// if tuile
        side_tuile = game->field[posx][posy+i];
        if (side_tuile.color == tuile->color && !col_form) {// if same color and not same form before
          col_color = true;
        }else if (side_tuile.form == tuile->form && !col_color) {// if same form and not same color before
          col_form = true;
        }else {
          if (!col_color && !col_form) {
            dialog("Down tile color and form doesn't match your tile");
          }else if (side_tuile.color == tuile->color && col_form) {
            dialog("Down tile color match but it's form line");
          }else if (side_tuile.form == tuile->form && col_color) {
            dialog("Down tile form match but it's a color line");
          }else{
            dialog("There's a mistake here");
          }
          return false;
        }
        i++;
      }
      i = 1;
      while (game->field[posx-i][posy].score > 0) {// if tuile
        side_tuile = game->field[posx-i][posy];
        if (side_tuile.color == tuile->color && !lig_form) {// if same color and not same form before
          lig_color = true;
        }else if (side_tuile.form == tuile->form && !lig_color) {// if same form and not same color before
          lig_form = true;
        }else {
          if (!lig_color && !lig_form) {
            dialog("Up tile color and form doesn't match your tile");
          }else if (side_tuile.color == tuile->color && lig_form) {
            dialog("Up tile color match but it's form line");
          }else if (side_tuile.form == tuile->form && lig_color) {
            dialog("Up tile form match but it's a color line");
          }else{
            dialog("There's a mistake here");
          }
          return false;
        }
        i++;
      }
      i = 1;
      while (game->field[posx+i][posy].score > 0) {// if tuile
        side_tuile = game->field[posx+i][posy];
        if (side_tuile.color == tuile->color && !lig_form) {// if same color and not same form before
          lig_color = true;
        }else if (side_tuile.form == tuile->form && !lig_color) {// if same form and not same color before
          lig_form = true;
        }else {
          if (!lig_color && !lig_form) {
            dialog("Up tile color and form doesn't match your tile");
          }else if (side_tuile.color == tuile->color && lig_form) {
            dialog("Up tile color match but it's form line");
          }else if (side_tuile.form == tuile->form && lig_color) {
            dialog("Up tile form match but it's a color line");
          }else{
            dialog("There's a mistake here");
          }
          return false;
        }
        i++;
      }
      // test si les 4 sont vides + bordures du terain
      // if (game->field[posx+1][posy].score+game->field[posx-1][posy].score+game->field[posx][posy+1].score+game->field[posx][posy-1].score == 0) {
      //   return false
      // }
      return true;
    }
  }
  dialog("Place is busy");
  return false;
}


int scorer(int posx, int posy, game * game)
{
  int score;
  score = 0; //+1 pour la piece posee
  int size_color_next = 0;
  int size_color_prev = 0;
  int size_form_next = 0;
  int size_form_prev = 0;
  int prev_posx, prev_posy;
  tuile * cur_tuile;
  tuile * save_tuile;
  char play[4];

  save_tuile = &game->field[posx][posy];
  cur_tuile = &game->field[posx][posy];
  int ascii = 96;

  // print_tuile(cur_tuile);

  while (cur_tuile) {
    prev_posx = cur_tuile->posx;
    prev_posy = cur_tuile->posy;
    cur_tuile = cur_tuile->next_color;
    if (cur_tuile) {
      log_char("Link next_color found !\n");
      sprintf(play, "%c%c%c%c\n", ascii+prev_posx,ascii+prev_posy,ascii+cur_tuile->posx,ascii+cur_tuile->posy);
      log_char(play);
      if (!was_played(play, game)) {
        log_char("Wasn't played !\n");
        size_color_next++;
      }
    }
  }
  cur_tuile = save_tuile;
  while (cur_tuile) {
    prev_posx = cur_tuile->posx;
    prev_posy = cur_tuile->posy;
    cur_tuile = cur_tuile->prev_color;
    if (cur_tuile) {
      log_char("Link prev_color found !\n");
      sprintf(play, "%c%c%c%c\n", ascii+prev_posx,ascii+prev_posy,ascii+cur_tuile->posx,ascii+cur_tuile->posy);
      log_char(play);
      if (!was_played(play, game)) {
        log_char("Wasn't played !\n");
        size_color_prev++;
      }
    }
  }
  cur_tuile = save_tuile;
  while (cur_tuile) {
    prev_posx = cur_tuile->posx;
    prev_posy = cur_tuile->posy;
    cur_tuile = cur_tuile->next_form;
    if (cur_tuile) {
      log_char("Link next_form found !\n");
      sprintf(play, "%c%c%c%c\n", ascii+prev_posx,ascii+prev_posy,ascii+cur_tuile->posx,ascii+cur_tuile->posy);
      log_char(play);
      if (!was_played(play, game)) {
        log_char("Wasn't played !\n");
        size_form_next++;
      }
    }
  }
  cur_tuile = save_tuile;
  while (cur_tuile) {
    prev_posx = cur_tuile->posx;
    prev_posy = cur_tuile->posy;
    cur_tuile = cur_tuile->prev_form;
    if (cur_tuile) {
      log_char("Link prev_form found !\n");
      sprintf(play, "%c%c%c%c\n", ascii+prev_posx,ascii+prev_posy,ascii+cur_tuile->posx,ascii+cur_tuile->posy);
      log_char(play);
      if (!was_played(play, game)) {
        log_char("Wasn't played !\n");
        size_form_prev++;
      }
    }
  }
  score += size_color_next + size_color_prev + size_form_next + size_form_prev;
  log_char("Score : ");log_int(score);
  return score;
}

bool was_played (char * cur_move, game * game)
{
  char move_reverse[4];
  move * new_move;

  // reverse relation
  move_reverse[0] = cur_move[2];
  move_reverse[1] = cur_move[3];
  move_reverse[2] = cur_move[0];
  move_reverse[3] = cur_move[1];

  // create a new move
  new_move = malloc(sizeof(*new_move));
  new_move->move[0] = cur_move[0];
  new_move->move[1] = cur_move[1];
  new_move->move[2] = cur_move[2];
  new_move->move[3] = cur_move[3];

  if (!game->moves) {
    log_char("First link\n");
    new_move->next = game->moves;
    game->moves = new_move;
    print_move(game->moves);
    return false;
  }

  move * next_move = game->moves;
  move * prev_move = game->moves;

  char str[20];
  while (next_move) {
    if (chcmp(cur_move, next_move->move)) {
      sprintf(str, "%s <-> %s \n", cur_move, next_move->move);
      log_char(str);
      log_char("Already linked\n");
      return true;
    }
    if (chcmp(move_reverse, next_move->move)) {
      sprintf(str, "%s <-> %s \n", move_reverse, next_move->move);
      log_char(str);
      log_char("Already linked\n");
      return true;
    }
    prev_move = next_move;
    next_move = next_move->next;
  }
  log_char("Add link\n");
  new_move->next = NULL;
  prev_move->next = new_move;

  return false;
}

void dialog(char * message)
{
  set_coord(1,14);
  printf("%s                                                        ", message);
}

tuile * draw_tuile(game * game)
{
  tuile * tuile = pop_link(game->deck);
  return tuile;
}
void link_tuile(int posx, int posy, tuile * tuile, game * game)
{
  if (posy-1 > 0 && game->field[posx][posy-1].score > 0) {
    log_char("link tuile up -> ");
    if (game->field[posx][posy-1].color == tuile->color) {
      log_char("same color -> ");
      game->field[posx][posy-1].next_color = tuile;
      tuile->prev_color = &game->field[posx][posy-1];
    }
    if (game->field[posx][posy-1].form == tuile->form ) {
      log_char("same form -> ");
      game->field[posx][posy-1].next_form = tuile;
      tuile->prev_form = &game->field[posx][posy-1];
    }
  }
  if (posy+1 < 12 && game->field[posx][posy+1].score > 0) {
    log_char("link tuile down -> ");
    if (game->field[posx][posy+1].color == tuile->color) {
      log_char("same color -> ");
      game->field[posx][posy+1].prev_color = tuile;
      tuile->next_color = &game->field[posx][posy+1];
    }
    if (game->field[posx][posy+1].form == tuile->form ) {
      log_char("same form -> ");
      game->field[posx][posy+1].prev_form = tuile;
      tuile->next_form = &game->field[posx][posy+1];

    }
  }
  if (posx-1 > 0 && game->field[posx-1][posy].score > 0) {
    log_char("link tuile left -> ");
    if (game->field[posx-1][posy].color == tuile->color) {
      log_char("same color -> ");
      game->field[posx-1][posy].next_color = tuile;
      tuile->prev_color = &game->field[posx-1][posy];
    }
    if (game->field[posx-1][posy].form == tuile->form ) {
      log_char("same form -> ");
      game->field[posx-1][posy].next_form = tuile;
      tuile->prev_form = &game->field[posx-1][posy];
    }
  }
  if (posx < 26 && game->field[posx][posy+1].score > 0) {
    log_char("link tuile right -> ");
    if (game->field[posx+1][posy].color == tuile->color) {
      log_char("same color -> ");
      game->field[posx+1][posy].prev_color = tuile;
      tuile->next_color = &game->field[posx+1][posy];
    }
    if (game->field[posx+1][posy].form == tuile->form ) {
      log_char("same form -> ");
      game->field[posx+1][posy].prev_form = tuile;
      tuile->next_form = &game->field[posx+1][posy];

    }
  }
}
void shuffle_list(list * deck)
{
  // print_list(game->deck);
  // shuffle it
  // struct tuile buf;
  // int k, random1, random2, n =35;
  // for(k = 0; k < n; k++){
  //   random1 = rand()%n;
  //   random2 = rand()%n;
  //   //printf("%d-%c -> %d-%c\n",random1,game->deck[random1].form, random2,game->deck[random2].form);
  //   buf = game->deck[random1];
  //   game->deck[random1] = game->deck[random2];
  //   game->deck[random2] = buf;
  //   //printf("%d-%c -> %d-%c\n",random1,game->deck[random1].form, random2,game->deck[random2].form, random2);
  // }
  // reset field
}
