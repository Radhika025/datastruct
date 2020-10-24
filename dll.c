#include"dll.h"
int count_nodes(List* dll){
	return dll->number_of_nodes; //return the number of nodes stored in the list 
}

void insert_front(List* dll, int data){

    struct Node* newnode = create_node(data); //creation of a new node by calling the create_node() function


    if(dll->head==NULL){ //checking if the list is empty 
        dll->head=newnode; //if it is pointing the head to the newly created node
        dll->tail=newnode; //tail also points to newly created node 
    }

    //if list is not empty
    else{
        newnode->next=dll->head; //newnodes next should point to wherever head is pointing to 
        newnode->prev=NULL; //new node acts as head hence newnodes prev should point to NULL
        dll->head->prev=newnode; //the node after newnodes prev should point to the newly created node
        dll->head=newnode; //head should finally point to the newnode thus completing the insertion 
    }

    //incrementing the count of nodes
    dll->number_of_nodes++;
    //printf("\n~%d~\n",dll->tail->data);
}

void dllist_delete_beginning(List* list){

    if(list->head==NULL){ //checking if the list is empty 
      //printf("--- UNDERFLOW! TRY ANOTHER OPTION ---\n");
      getchar(); 
      return; 
    }
    struct Node* aux = list->head; //we make an aux node which stores the head node
    //for the purpose of freeing the aux/head node later on 

    if(list->number_of_nodes==1) //if theres only one node in the list
    {
        list->head=NULL; //list is empty when head is NULL, so we set head to NULL when only one node present
        list->tail=NULL; 
        list->number_of_nodes=0; //set count of nodes to 0 
        free(aux);
        return; 
    }

    else{
        //head node to be deleted
        list->head=list->head->next; //head node should point to the node next to itself
        //head now now pointing to the prev 2nd node in the list
        list->head->prev=NULL; //setting the new heads prev to NULL 
        
        
        //decrementing count of lists
        list->number_of_nodes--; 

        //freeing the original head
        free(aux);
    }
}


void position_delete(List* dll, int pos){   

    if(pos<0 || pos>=dll->number_of_nodes){ //checking if user inputs numbers only within the count of nodes
        //printf("--- INVALID POSITION, TRY ANOTHER NUMBER ---\n");
        return; 
    }

    if(pos==0){ //if pos is 0, we call the function written for deletion at beg 
        dllist_delete_beginning(dll);
        return;
    }

    if(pos == dll->number_of_nodes-1){ //if the pos is count-1, ie last node

        //delnode is created to point to the last node's previous node
        //last nodes address is with the tail hence
        Node* delnode=dll->tail->prev; 

        //temp is created to store the last node which is to be deleted 
        Node* temp=delnode->next;
        delnode->next=NULL; //last node's next should point to NULL 

        //last node is deleted 
        free(temp);

        //decrementing number of nodes
        dll->number_of_nodes--;
        return;
    }
    
    Node* temp=dll->head; //previous node of the node to be deleted 
    int i=0;
    while(i<pos-1) //stop at the node which is previous to the node to be deleted. pos-1 when we are considering the indices 
    {
        temp=temp->next;
        i++;
    }


    //del node stores the address of the node to be deleted 
    Node* del=temp->next;


    //nexdel node stores the address of the node after the node to be deleted node 
    Node* nexdel=(temp->next)->next;


    //curr node stores the address of the node before the node to be deleted node 
    Node* prevdel=temp;



    //we make the previous nodes point to the next node of the node to be deleted
    prevdel->next=nexdel;
    //we make the next node point to previous of the node to be deleted 
    nexdel->prev=prevdel;


    //deletion of the node to be deleted 
    free(del);

    //decrementing count of nodes
    dll->number_of_nodes--;
    return;
    
}


int search_list(List* dll,int key){

    if(dll->head==NULL){ //if the list is empty 
        //printf("---UNDERFLOW---\n"); 
        return 0; 
    }

    //aux node is made to check each node and compare with the key
    struct Node* aux=dll->head; //aux points to start of the node
    
    //for loop iterates through the entire list 
    for(int i=0; i<dll->number_of_nodes; i++){
        if(aux->data==key){ //comparing the key to each nodes data
            return i; //return the index if found
        }
        aux=aux->next; //traversing through the list if not
    }
    return -1; //return -1 if not found
}


void reverse_list(List* dll){ 
    if(dll->number_of_nodes == 0){ //checking if list is empty 
        //printf("---UNDERFLOW---\n"); 
        return;
    }

    //current node traverses the entire list
    //temp points to the node next to current
    //temp is used to store the next nodes address as when we swap the links, we need to 
    //store the next nodes address separately as it is lost when we do
    //current->next = current->prev;

    Node *current = dll->head; //current points to lists start
    int i = 0;


    while(i < dll->number_of_nodes){ //traversing through the list
        if(i == dll->number_of_nodes -1){ //for the last most node
            dll->tail = dll->head; //swapping of head and tail
            dll->head = current; //make head point to current
 
        }
        Node *temp = current->next; //temp is made to point to the node next to current

        //swapping the links 
        current->next = current->prev;
        current->prev = temp;

        i++;//for the loop

        //traversing the node, as temp has the address of the next node
        current = temp;
    }
}



