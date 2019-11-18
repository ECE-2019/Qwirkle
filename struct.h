#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

typedef struct Tuile
{
  int color;
  int form;
  int score;
  int posx;
  int posy;
  struct Tuile * next_color;
  struct Tuile * prev_color;
  struct Tuile * next_form;
  struct Tuile * prev_form;
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

typedef struct Move
{
  char move[4];
  struct Move * next;
} move;

typedef struct Game
{
  int mode;
  int nb_player;
  int play;
  list * deck;
  player * players;
  move * moves;
  tuile field[26][12];
} game;

typedef struct Score
{
  char pseudo[15];
  int score_game;
} score;

typedef enum
{
  false,
  true
} bool;

#endif // STRUCT_H_INCLUDED
