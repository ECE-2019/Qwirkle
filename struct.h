#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct Tuile
{
  int color;
  int form;
  int score;
} tuile;

typedef struct List
{
  int color;
  int form;
  int score;
  tuile * tuile;
  struct List * next;
} list;

typedef struct Player
{
  char pseudo[15];
  int score_game;
  int score_play;
  list * hand;
} player;

typedef struct Game
{
  player * players;
  list * pioche;
  tuile field[26][12];
  int mode;
  int nb_player;
} game;

typedef enum
{
  false,
  true
} bool;

#endif // STRUCT_H_INCLUDED
