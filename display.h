#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "prototype.h"

/* Prototype */
void display_menu();
void display_select_mode();
void display_select_player_number();
void display_hud();
void display_field(game * game);
void display_options();
void display_quit();
void display_score();
void display_ask_save();
void display_bye();
void display_welcome();

/* Function */
void display_menu()
{
  system("cls");
  puts("\n***********************MENU***********************\n");
  puts("\t New game");
  puts("\t Saved games");
  puts("\t Leaderboard");
  puts("\t Options");
  puts("\t Quit");
}
void display_select_mode()
{
  system("cls");
  puts("\n*********************Select a mode*********************\n");
  puts("\t Quick");
  puts("\t Normal");
}
void display_select_player_number()
{
  system("cls");
  puts("\n************Number of player (2-4)************\n");
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
  puts("Rules :");
  puts("\tLe Qwirkle est un jeu qui se joue a plusieur (2-4 joueurs)");
  puts("\tJeu tactique d'association et de logique. 2 à 4 joueurs.");
  puts("\tChaque joueur dispose de 6 tuiles.");
  puts("\tA son tour il en place un maximum à condition de les poser sur une seule ligne,");
  puts("\tavec un caractère commun: la couleur ou la forme.");
  puts("\tA chaque tour on marque les points des lignes que l'on a complétées.");
  puts("\tL'astuce consiste à placer ses pièces à des endroits stratégiques,");
  puts("\tcomme par exemple des intersections, pour marquer un maximum de points");
  while (!getch()) {
    return;
  }
}
void display_quit()
{
  system("cls");
  reset_color();
  puts("\n************Are you sure to leave the game ?************\n");
  puts("\t yes");
  puts("\t no");
}
void display_ask_save()
{
  system("cls");
  puts("\n************Your about to leave. Would you like to save ?************\n");
  puts("\t yes");
  puts("\t no");
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
  Sleep(2000);
  reset_color();
}

#endif // DISPLAY_H_INCLUDED
