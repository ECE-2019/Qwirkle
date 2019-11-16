#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

/* Prototype */
void set_coord(int x, int y);
void set_color(int color_text,int color_background);
void reset_color();
void get_key(int * key);
void log_char(char * message);
void log_int(int message);
bool chcmp(char * chain1, char * chain2);

/* Function */
void set_coord(int x, int y)
{
  COORD mycoord;
  mycoord.X = x;
  mycoord.Y = y;
  SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
void set_color(int color_text,int color_background)
{
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H,color_background*16+color_text);
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
void reset_color()
{
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H,0*16+15);
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
void log_char(char * message)
{
  FILE *f;
  f = fopen("qwirkle.log", "a"); // a+ (create + append) option will allow appending which is useful in a log file
  if (f == NULL) { /* Something is wrong   */}
  fprintf(f, message);
  fclose(f);
  return;
}
void log_int(int number)
{
  FILE *f;
  f = fopen("qwirkle.log", "a"); // a+ (create + append) option will allow appending which is useful in a log file
  if (f == NULL) { /* Something is wrong   */}
  char str[10];
  sprintf(str, "%d\n", number);
  fprintf(f, str);
  fclose(f);
}
bool chcmp(char * chain1, char * chain2)
{
  int chain1_length, chain2_length, i;
  chain1_length = sizeof(chain1)/sizeof(chain1[0]);
  chain2_length = sizeof(chain2)/sizeof(chain2[0]);
  if (chain1_length != chain2_length) {
    return false;
  }
  for (i = 0; i < chain1_length; i++) {
    if (chain1[i] != chain2[i]) {
      return false;
    }
  }
  return true;
}

#endif // TOOLS_H_INCLUDED
