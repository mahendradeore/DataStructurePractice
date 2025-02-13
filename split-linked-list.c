#include <stdio.h>
#include <stdlib.h>
// To execute C, please define "int main()"

/*
1->2->3->4->5. .... ->1

1->2->3 ... ->1
4->5 ... -> 4
*/

typedef struct node {
  int data;
  struct node *next;
}Node;





void insertNode(int data, Node **head, Node **tail){

  Node *node = (Node*)malloc(sizeof(struct node));
  node->data = data;
  node->next = NULL;
  if(*head == NULL){
      *head = node;
      //*head->next = NULL;
      *tail = *head;
  }else {
    node->next = *head;
    *head = node;
  }

}

void printList(Node *head){
  if(head == NULL){
    printf("\nList is empty unable to print");
    return;
  }

  Node *temp = head;
  do{
    
    printf("\n data %d",temp->data);
    temp= temp->next;
  }while(temp != head);

}


void splitlist(Node **head,Node **head1, Node**head2){

//empty node
  if(*head == NULL){
    printf("\nList is empty");
    return;
  }
  Node *fast = NULL;
  Node *slow = NULL;
  fast = slow = *head;

 //only 1 node
  if(slow->next == *head)
  {
    printf("\nList contains only 1 node");
    *head1 = slow;
    *head2  = NULL;
    return;
  }
  //only 2 nodes
  if(fast->next->next == *head){
    *head1 = slow;
    *head2 = fast->next->next;
    (*head1)->next = *head1;
    (*head2)->next = *head2;
  }
  while(fast->next != *head && fast->next->next != *head){
    slow = slow->next;
    fast = fast->next->next;
  }
  if(fast->next->next == *head){
    fast = fast->next;
  }
  *head1 = *head;
  *head2 = slow->next;
  fast->next = *head2;
  slow->next = *head1;
}
int main() {

  Node *head = NULL;
  Node *tail = NULL;
  Node *head1 = NULL;
  Node *head2 = NULL;
  insertNode(6,&head,&tail);
   insertNode(5,&head,&tail);
  //  insertNode(4,&head,&tail);
  // insertNode(3,&head,&tail);
  // insertNode(2,&head,&tail);
  // insertNode(1,&head,&tail);
  if(tail)
    tail->next = head;
  printList(head);
  splitlist(&head,&head1,&head2);
  printf("\nlist 1");
  printList(head1);
  printf("\nlist 2");
  printList(head2);

 

 
}


