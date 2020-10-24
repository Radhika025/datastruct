#include<stdio.h>
#include<stdlib.h>
#include "sll.h"

void insert_at_end(List *list, int data) {
	Node *newnode = (Node*) malloc(sizeof(Node)); //mem. allocation of a newnode
	//Initializing new node. 
	newnode->data=data; //Initializing data to the value passed to the function
	newnode->link=NULL; //Initializing it to NULL
	if(list->head==NULL){ //checking if list is empty
		list->head = newnode; //Setting the head to wherever newnode points to
	}
	else{
		Node *aux =  list->head;
		//aux node is made to trasverse from the start of the link till the end of the link
		while(aux->link!=NULL){ //end node always points to NULL so checking for NULL 
			aux = aux->link; //traversing 
		}
		//on aux reachinf the last node, aux's link should point to newnode
		aux->link=newnode; //newnode added to the list at end
	}
	list->number_of_nodes++; 
}

void list_delete_front(List* list) {
	if(list->head==NULL|list->number_of_nodes==0){ //checks if the list is empty 
		printf("UNDERFLOW, OPERATION COULD NOT BE PERFORMED. ENTER ANOTHER CHOICE\n"); 
	}
	else{
		Node *aux = list->head; //declaration of an aux node and setting it to head 
		list->head = aux->link; //setting head to the next node of the first node 
		//since we cant directly write list->head=list->head->link
		free(aux); //we delete or free the memory of the aux node
		list->number_of_nodes--; //decrement the number of nodes in list by 1
	}
}

void list_insert_at (List*list, int data, int position) {
	Node *newnode = (Node*) malloc(sizeof(Node)); //mem. allocation of a newnode
	//Initializing new node. 
	newnode->data=data; //Initializing data to the value passed to the function
	newnode->link=NULL; //Initializing link to NULL. 
	if(position == 0 && list->head==NULL){
		list->head = newnode; //Setting the head to wherever newnode points to
	}
	else if(position == 0){
        newnode->link=list->head; //set the newnodes link point to wherever head points to
		list->head=newnode; //then point the head to the newly added node
	}
	else if(position <= list->number_of_nodes && position>0){
		Node* aux = list->head; //making an aux node pointer to 
		//point to the (position-1)th node 
		//for loop to traverse till position-1 
		for (int i = 1; i < position; i++) {
            if (i == position-1){ //on the (position-1)th node 
                newnode->link = aux->link; //newnode point to the (position-1)th node's link ie. point to position's node's address 
                aux->link = newnode; //the aux or (position-1)th node's link point to new node
            }
            aux = aux->link; //traverse through list 
        }
	}
	list->number_of_nodes++; //increment the node counter of list by 1
}

void list_reverse(List* list)
{ 
	//three pointers 
	//pointer to the previous node of the node we are traversing through
 	Node* prev = NULL;
	//pointer to the node which traverses through the list
	Node* curr = list->head; 
	//pointer to the next node of the node we are traversing through
	Node* next = NULL;  
	while(curr != NULL){ //as long as current is not NULL as curr cannot be last element
		next = curr->link; //next points to the node after curr
		curr->link=prev; //loops around the whole list inorder to reverse
		prev = curr; 
		curr = next; 
	}
	list->head=prev; //remaking the head to the previous node 
}


