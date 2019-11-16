#ifndef PROTOTYPE_H_INCLUDED
#define PROTOTYPE_H_INCLUDED

#include "tools.h"

/* Prototype */
bool is_empty_list(list * list);
int list_length(list * list);
void update_link_at(list * list, tuile * tuile, int pos);
list * new_link(tuile * tuile);
list * push_link(list * list, tuile * tuile);
list * add_link_at(list * list, tuile * tuile, int pos);
list * remove_link_at(list * list, int pos);
tuile * get_link_at(list * list, int pos);
tuile * new_struct(int color, int form, int score);
tuile * pop_link(list * list);

void print_list(list * list);
void print_tuile(tuile * tuile);
void print_move(move * move);
void print_move_list(move * move);

/* Function */
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
  tuile->posx = -1;
  tuile->posy = -1;
  tuile->next_color = NULL;
  tuile->prev_color = NULL;
  tuile->next_form = NULL;
  tuile->prev_color = NULL;
  return tuile;
}
void free_moves()
{
  // Free moves

  // if(list->next == NULL){
  //   free(list);
  //   return NULL;
  // }
  //
  // struct List * temp = list;
  // struct List * before = list;
  //
  // while (temp->next != NULL) {
  //   before = temp;
  //   temp = temp->next;
  // }
  // before->next = NULL;
  // //free(temp);
  //
  // return temp->tuile;
}

void print_list(list * list)
{
  if (is_empty_list(list)) {
    log_char("List empty");
    return;
  }
  while (list) {
    //char * str;
    //sprintf(str, "[%d %c %d]\n", list->tuile->color, list->tuile->form, list->tuile->score);
    //log_char(str);
    print_tuile(list->tuile);
    list = list->next;
  }
  return;
}
void print_tuile(tuile * tuile)
{
  char structure[70];
  sprintf(structure,"Tuile\n{\n\t%d\n\t%d\n\t%d\n\t%d\n\t%d\n\t%p\n\t%p\n\t%p\n\t%p\n}\n",
  tuile->color,tuile->form,tuile->score,tuile->posx,tuile->posy,tuile->next_color,tuile->prev_color,tuile->next_form,tuile->prev_form);
  log_char(structure);
}
void print_move(move * move)
{
  char structure[25];
  //int ascii = 96;
  sprintf(structure,"Move\n{\n\t%c%c%c%c\n}\n",
  move->move[0],move->move[1],move->move[2],move->move[3]);
  log_char(structure);
}
void print_move_list(move * move)
{
  while (move) {
    print_move(move);
    move = move->next;
  }
}

#endif // PROTOTYPE_H_INCLUDED
