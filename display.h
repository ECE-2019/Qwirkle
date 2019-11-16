#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "prototype.h"

void display_menu();
void display_select_mode();
void display_select_player_number();
void display_hud();
void display_field(game * game);
void display_bye();
void display_welcome();
void display_options();
void display_score();

void display_menu()
{
  system("cls");
  puts("\n***********************MENU***********************\n");
  puts("\t Demarrer une nouvelle partie");
  puts("\t Reprendre la partie en cours");
  puts("\t Consulter les scores");
  puts("\t Consulter les options");
  puts("\t Quitter le jeu");
}

void display_select_mode()
{
  system("cls");
  puts("\n*********************Choisissez un mode*********************\n");
  puts("\t Degrade");
  puts("\t Normal");
}

void display_select_player_number()
{
  system("cls");
  puts("\n************Choisissez un nombre de joueur (2-4)************\n");
  puts("\t 2");
  puts("\t 3");
  puts("\t 4");
}

void display_hud()
{
  system("cls");
  puts(" abcdefghijklmnopqrstuvwxyz\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl");
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

void display_options()
{
  system("cls");
  puts("Options");
  while (!getch()) {
    /* code */
  }
}
void display_welcome()
{
  system("cls");
  set_color(12,0);
  puts("\n\n");
  puts(" ________  ___       __   ___  ________  ___  __    ___       _______      ");
  puts("|\\   __  \\|\\  \\     |\\  \\|\\  \\|\\   __  \\|\\  \\|\\  \\ |\\  \\     |\\  ___ \\     ");
  puts("\\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\    \\ \\   __/|    ");
  puts(" \\ \\  \\\\\\  \\ \\  \\  __\\ \\  \\ \\  \\ \\   _  _\\ \\   ___  \\ \\  \\    \\ \\  \\_|/__  ");
  puts("  \\ \\  \\\\\\  \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\\\  \\\\ \\  \\\\ \\  \\ \\  \\____\\ \\  \\_|\\ \\ ");
  puts("   \\ \\_____  \\ \\____________\\ \\__\\ \\__\\\\ _\\\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\");
  puts("    \\|___| \\__\\|____________|\\|__|\\|__|\\|__|\\|__| \\|__|\\|_______|\\|_______|");
  puts("          \\|__|");
  puts("\t\tBy EvergreenVen & Minaro from the Qwirkle Team ©");
  //Sleep(2000);
  reset_color();
}

void display_bye()
{
  system("cls");
  set_color(12,1);
  puts("\n\n");
  puts("________      ___    ___ _______           ________      ___    ___ _______      ");
  puts("|\\   __  \\    |\\  \\  /  /|\\  ___ \\         |\\   __  \\    |\\  \\  /  /|\\  ___ \\     ");
  puts("\\ \\  \\|\\ /_   \\ \\  \\/  / \\ \\   __/|        \\ \\  \\|\\ /_   \\ \\  \\/  / \\ \\   __/|    ");
  puts("\\ \\   __  \\   \\ \\    / / \\ \\  \\_|/__       \\ \\   __  \\   \\ \\    / / \\ \\  \\_|/__  ");
  puts(" \\ \\  \\|\\  \\   \\/  /  /   \\ \\  \\_|\\ \\       \\ \\  \\|\\  \\   \\/  /  /   \\ \\  \\_|\\ \\ ");
  puts("  \\ \\_______\\__/  / /      \\ \\_______\\       \\ \\_______\\__/  / /      \\ \\_______\\");
  puts("   \\|_______|\\___/ /        \\|_______|        \\|_______|\\___/ /        \\|_______|");
  puts("            \\|___|/                                    \\|___|/      ");
  Sleep(3000);
  reset_color();
  system("cls");
}

#endif // DISPLAY_H_INCLUDED
