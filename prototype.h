#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

/* Prototype */
void set_coord(int x, int y);
void set_color(int color_text,int color_background);
void reset_color();
void get_key(int * key);

bool is_empty_list(list * list);
int list_length(list * list);
void print_list(list * list);
void update_link_at(list * list, tuile * tuile, int pos);
list * new_link(tuile * tuile);
list * push_link(list * list, tuile * tuile);
list * add_link_at(list * list, tuile * tuile, int pos);
list * remove_link_at(list * list, int pos);
tuile * get_link_at(list * list, int pos);
tuile * new_struct(int color, int form, int score);

void log_char(char * message);
void log_int(int message);

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

bool is_empty_list(list * list)
{
  if (list) {
    return false;
  }
  return true;
}
int list_length(list * list)
{
  int size_l = 0;
    while (list) {
      size_l++;
      list = list->next;
    }
  return size_l;
}
void print_list(list * list)
{
  //system("cls");
  if (is_empty_list(list)) {
    log_char("List empty");
    return;
  }
  //char * str;
  while (list) {
    printf("[%d %c %d]\n", list->tuile->color, list->tuile->form, list->tuile->score);
    //sprintf(str, "[%d %c %d]\n", list->tuile->color, list->tuile->form, list->tuile->score);
    list = list->next;
  }
  //log_char(str);
  return;
}
void update_link_at(list * list, tuile * tuile, int pos)
{
  int i = 0;
  if(is_empty_list(list)){
    puts("List empty");
    return;
  }
  if (pos >= list_length(list)) {
    log_char("Pos doesn't exist in the current list");
    return;
  }
  while (i < pos) {
    i++;
    list = list->next;
  }
  list->tuile = tuile;
  return;
}
list * new_link(tuile * tuile)
{
  list * link = malloc(sizeof(*link));
  //if malloc NULL
  link->tuile = tuile;
  link->next = NULL;

  return link;
}
list * push_link(list * list, tuile * tuile)
{
  struct List * link = new_link(tuile);

  if(is_empty_list(list)){
    return link;
  }

  struct List * temp = list;

  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = link;

  return list;

}
tuile * pop_link(list * list)
{
  if(is_empty_list(list)){
    log_char("List empty\n");
    return NULL;
  }
  if(list->next == NULL){
    free(list);
    return NULL;
  }

  struct List * temp = list;
  struct List * before = list;

  while (temp->next != NULL) {
    before = temp;
    temp = temp->next;
  }
  before->next = NULL;
  //free(temp);

  return temp->tuile;

}
list * add_link_at(list * list, tuile * tuile, int pos)
{
  struct List * link_prec = list;
  struct List * link_curr = list;
  struct List * link = new_link(tuile);
  int i = 0;

  if(is_empty_list(list)){
    return link;
  }
  if (pos >= list_length(list)) {
    log_char("Pos doesn't exist in the current list\n");
    return NULL;
  }
  if (pos == 0) {
    link->next  = list;
    return link;
  }
  while (i < pos) {
    i++;
    link_prec = link_curr;
    link_curr = link_prec->next;
  }
  link_prec->next = link;
  link->next = link_curr;

  return list;
}
list * remove_link_at(list * list, int pos)
{
  struct List * link_prec = list;
  struct List * link_curr = list;
  int i = 0;

  if(is_empty_list(list)){
    return NULL;
  }
  if (pos >= list_length(list)) {
    log_char("Pos doesn't exist in the current list\n");
    return NULL;
  }
  if (pos == 0) {
    list = list->next;
    free(link_curr);
    return list;
  }
  while (i < pos) {
    i++;
    link_prec = link_curr;
    link_curr = link_prec->next;
  }
  link_prec->next = link_curr->next;
  free(link_curr);
  return list;
}
tuile * get_link_at(list * list, int pos)
{
  int i = 0;
  if (is_empty_list(list)) {
    log_char("List empty");
    return NULL;
  }
  if (pos >= list_length(list)) {
    log_char("Pos doesn't exist in the current list");
    return NULL;
  }
  while (i < pos) {
    list = list->next;
    i++;
  }
  return list->tuile;
}
tuile * new_struct(int color, int form, int score)
{
  tuile * tuile = malloc(sizeof(*tuile));
  tuile->color = color;
  tuile->form = form;
  tuile->score = score;
  return tuile;
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
#endif // PROTOTYPE_H_INCLUDED
