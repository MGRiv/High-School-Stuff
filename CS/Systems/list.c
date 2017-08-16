#include <stdio.h>
#include <stdlib.h>

struct node{ int val;struct node* next;};

void print_list(struct node *l){
  while(l != NULL){
    printf("%d ",l->val);
    l = l->next;
  }
}

struct node *insert_front(struct node *point,int v){
  struct node *n = (struct node *)malloc(sizeof(struct node));
  n->val = v;
  n->next = point;
  return n;
}

struct node *free_list(struct node *point){
  if(point != NULL){
    free_list(point->next);
    free(point);
  }
  return point;
}

int main(){
  struct node *list = (struct node *)malloc(sizeof(struct node));
  list->val = 1;
  list->next = NULL;
  print_list(list);
  printf("\nAdd 7 to list\n");
  list = insert_front(list,7);
  print_list(list);
  printf("\nFree list\n");
  free_list(list);
  printf("\n%d",list->val);
}
