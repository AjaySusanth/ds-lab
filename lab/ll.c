#include <stdio.h>
#include <stdlib.h>

/*FUNCTIONS
    INSERT - front,end,specific
    DELETE - front,end,specific
    REVERSE LL
    FIND MIDDLE ELT
    DELETE MIDDLE ELT
    DETECT LOOP
    STARTING NODE OF LOOP
*/

struct Node {
    int data;
    struct Node *link;
};

struct Node *head = NULL;

void display() {
    if (head == NULL){
         printf("List empty");
         return;
    }
    
    struct Node *temp = head;
    while(temp!=NULL) {
        printf("%i\t",temp->data);
        temp = temp->link;0
    }
    printf("\n");
}


void insert_end(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;
    if (head == NULL){
         head = newNode;
         return;
    }
    struct Node *temp = head;
    while(temp->link!=NULL)
        temp = temp->link;
    temp->link = newNode;
}

void insert_front(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = head;
    head = newNode;
}

void insert_after(int data,int key) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;
    
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node *temp = head;
    
    while(temp->link!=NULL && temp->data!=key)
        temp = temp->link;
    
    if(temp->data!=key) {
        printf("Key not found\n");
        return;
    }
    
    newNode->link = temp->link;
    temp->link = newNode;
    
}

void delete_front() {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    struct Node *temp = head;
    head = head->link;
    free(temp); 
}

void delete_end() {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    if(head->link == NULL) {
        struct Node *temp = head;
        head = head->link;
        free(temp);
        return;
    }
    
    struct Node *prev = head, *curr = head->link;
    
    while(curr->link!=NULL) {
        prev = curr;
        curr = curr->link;
    }
    
    prev->link = NULL;
    free(curr);
    
}

void delete_key(int key) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    if(head->data == key) {
        struct Node *temp = head;
        head = head->link;
        free(temp);
        return;
    }
    
     struct Node *prev = head, *curr = head->link;
     
     while(curr->link!=NULL && curr->data!=key) {
        prev = curr;
        curr = curr->link;
    }
    
    if(curr->data!=key) {
        printf("Key not found\n");
        return;
    }
    
    prev->link = curr->link;
    free(curr);
}


void reverse() {
    struct Node *prev,*curr,*next;
    if (head == NULL){
         printf("List empty");
         return;
    }
    prev=NULL;
    curr=next=head;
    while(next!=NULL) {
        next = next->link;
        curr->link = prev;
        prev=curr;
        curr=next;
    }
    head = prev;
}


struct Node *middle() {
    struct Node *slow,*fast;
    if (head == NULL){
         printf("List empty");
         return NULL;
    }
    slow = head;
    fast = head;
    
    while(fast!=NULL && fast->link!=NULL) {
        slow = slow->link;
        fast = fast->link->link;
    }
    return slow;
}
/*
ALTERNATE METHOD TO FIND MIDDLE:

Find the length of the ll
if odd, mid = len+1/2
if even , mid = len/2+1
*/

void deleteMiddle() {
    struct Node *slow,*fast;
    if (head == NULL){
         printf("List empty");
         return;
    }
    
    slow = fast = head;
    fast = fast->link->link;
    while(fast!=NULL && fast->link!=NULL){
        slow =slow->link;
        fast = fast->link->link;
    }
    
    struct Node *temp =slow->link;
    slow->link = slow->link->link;
    free(temp);
}

// Detecting if the linkedlist contains cycle.
bool isLoop() {
    struct Node *slow,*fast;
    if (head == NULL){
         printf("List empty");
         return false;
    }
    slow = head;
    fast = head;
    
    while(fast!=NULL && fast->link!=NULL) {
        slow = slow->link;
        fast = fast->link->link;
        if(slow == fast)
            return true;
    }
    return false;
}

// Finding the starting node of cycle
struct Node *startingLoop () {
    
    struct Node *slow,*fast;
    if (head == NULL){
         printf("List empty");
         return NULL;
    }
    slow = head;
    fast = head;
    
    while(fast!=NULL && fast->link!=NULL) {
        slow = slow->link;
        fast = fast->link->link;
        if(slow == fast) {
            slow = head;
            while(slow!=fast) {
                slow = slow->link;
                fast = fast->link;
            }
            return slow;
        }
    }
    return NULL;
    
}

struct Node *findCommon(struct Node *head1,struct Node *head2) {
    struct Node *common=NULL,*temp1=head1,*temp2=NULL;
    
    while(temp1!=NULL){
        temp2=head2;
        while(temp2!=NULL) {
            if(temp1->data == temp2->data)
                common = insert(common,temp1->data);
            temp2 = temp2->link;
        }
        temp1=temp1->link;
    }
    return common;
}




int main() {
    insert_end(2);
    insert_end(10);
    insert_end(25);
    insert_end(3);
    insert_end(1);
    insert_end(11);
    
    display();
    reverse();
    display();
    struct Node *midNode = middle();
    printf("%i\n",midNode->data);
    deleteMiddle();
    display();
    return 0;
}