#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
  smaller = NULL;
  larger = NULL;
  help_pivot(head, smaller, larger, pivot);
}

void help_pivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
  if(head == NULL){return;}
  help_pivot(head->next, smaller, larger, pivot);
  if(head->val <= pivot){
    head->next = smaller;
    smaller = head;
    head = NULL;
    return;
  }
  else if(head->val > pivot){
    head->next = larger;
    larger = head;
    head = NULL;
    return;
  }
}
