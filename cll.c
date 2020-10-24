#include "cll.h"
void position_insert(List* cll, int data, int pos){


    //creation of node 
    Node* newnode = create_node(data); //newnode stores the data passed by user and creates a node


    //for invalid positions 
    if(pos>cll->length || pos<0){
        printf("ENTER A VALID INDEX\n");
        printf("Enter between 0 and %d\n", cll->length-1); 
        return; 
    }


    //for start
    if(pos == 0){ //checking if the position given is the start of the list
    
        if(cll->head==NULL){ //checking if list is null

            cll->head = newnode; //head points to newnode
            newnode->next = newnode; //circular list, hence first node points to itself
            cll->tail = newnode; //tail points to the last node 

        }
        else{ //if list is not empty and node to be added in the front of the list 

            Node* temp = cll->head; //temp node pointing to head 
            cll->head = newnode; //head points to newnode 
            newnode->next = temp; //newnode added should point to the node in the list 
            cll->tail->next = cll->head; //tail points to the head to implement circular list 

        }

    }


    //for last node 
    else if( cll->head != NULL && pos==(cll->length)-1 ){ //when the position is the last node 
        cll->tail->next = newnode; //last node linked with new node
        cll->tail = newnode; //last node made tail
        newnode->next = cll->head; //implementing circular list 
    }


    //for nodes which are not start or last 
    else{
        Node* temp = cll->head; //temp pointing to head 
        for(int i=0; i<pos-1; i++){ //loop till we traverse to the node previous of the pos' node
            temp=temp->next; //traversing 
        }

        //temp at the node previous to the pos' node
        newnode->next=temp->next; //making newnode point to the pos node 
        temp->next=newnode; //previous to the pos' node should point to the new node
    }


    //incrementing 
    cll->length++;
}

void position_delete(List* cll, int pos){
//to delete the node at a position 


    //for invalid, overflow and underflow cases
    if((pos<0) || (pos>=cll->length) || (cll->length==0)){
        printf("INVALID INDEX ENTERED\n"); 
        return;
    }  


    //position is 0, ie first node and length is 1  
    else if( (pos==0) && (cll->length==1)){
        Node* temp=cll->head; //temp points to the head of the list 

        //freeing the previous head 
        free(temp);

        //head and tail made to NULL
        cll->head=NULL;
        cll->tail=NULL;
    }
    

    //if the pos is 0 when the length is more than 1
    else if(pos==0){
        Node* temp=cll->head; //temp is made to point to head 
        cll->head=cll->head->next; //head is made to point to the node next to it 
        free(temp); //head is freed 
        cll->tail->next=cll->head; //tail is made to point to the head to maintain circularity 
        
    }


    //when last node is to be deleted 
    else if(pos==cll->length-1){
        Node* temp=cll->head; //temp is made to point to head 
        while(temp->next!=cll->tail){ //temp traverses until the node previous to the tail
            temp=temp->next; //traversing
        }
        Node* del=temp->next; //del at the last node 
        temp->next=cll->head; //temp, last nodes previous node is made to point to the head to maintain circularity 
        
        free(del); //last node is freed
        cll->tail=temp; //tail is set to the last node (previous of last node)
    }


    //specified position
    else
    {   
        Node* temp=cll->head;
        Node* del; 
        
        for(int i=0;i<pos; i++){ //traverses to the node previous to the pos' node
            temp=temp->next;
        }

        del=temp->next; //del is set to the node next to the to be deleted node  
        free(del); //node to be deleted is freed 
        temp->next=cll->head; 
        cll->tail=temp;
        
    }

    cll->length--; //decrementing the node 
}

int josephus(List* cll, int k){


    //survive node goes till the kth node, ((k-1)th indexed node)  
    //note that kth node is (k-1) index 
    //hence loop goes till k-1 / i<k 
    //kill node is the node next to the kth node, ((k)th indexed node)  

    Node *survive = cll->head;
    Node *kill = NULL;


    for (int i=0;i<k;i++) //loop to go till the kth node 
        survive = survive->next;


    if (k==-1) //last node 
        survive=cll->tail;
 
 
    while (cll->length>1){ //loop is ran till the list has 1 element 

        //deletion part, deleting the kth node 
        kill=survive->next; //assigning kill to the kth's next node 
        survive->next= kill->next; //survives next should point to the node after k

        //deletion od the kth node
        free(kill);


        cll->length--;

        //changing the kth node to the node next to it  
        survive = survive->next;
        //repeat till one survivor survives 
    }

    //only one node remains, hence head and tail both points to the same node which is survive
    cll->head = survive;
    cll->tail = survive; 

    //returns whatever the survives value is 
    return survive->data;
}