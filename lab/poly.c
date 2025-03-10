#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff,expo;
    struct Node *link;
};

struct Node *createNode() {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->link =NULL;
    return newNode;
}

struct Node *readPoly() {
    int n;
    struct Node *head = NULL;
    printf("Enter the no.of terms in poly\n");
    scanf("%i",&n);
    for(int i=0;i<n;i++) {
        struct Node *newNode = createNode();
        printf("Enter the coeff\n");
        scanf("%i",&newNode->coeff);
        printf("Enter the expo\n");
        scanf("%i",&newNode->expo);
        if(head == NULL)
            head = newNode;
        else {
            struct Node *temp = head;
            while(temp->link!=NULL)
                temp = temp->link;
            
            temp->link = newNode;
        }
    }
    return head;
}

void display(struct Node *head) {
    if(head == NULL){
        printf("Poly empty\n");
        return;
    }
    
    struct Node *temp = head;
    while(temp->link!=NULL) {
        if(temp->coeff!=0) {
            if(temp->expo!=0) {
                printf("%ix^%i+",temp->coeff,temp->expo);
            }
            else {
                printf("%i+",temp->coeff);
            }
        }
        temp = temp->link;
    }
    
    if(temp->coeff!=0) {
        if(temp->expo!=0) {
            printf("%ix^%i",temp->coeff,temp->expo);
        }
        else {
            printf("%i",temp->coeff);
        }
    }
    printf("\n");
}

struct Node * multiply(struct Node *phead,struct Node *qhead) {
     struct Node *p,*q,*rhead=NULL,*r,*prev;
     
    p=phead;
    q=qhead;
    r=rhead;
    
    while(p!=NULL) {
        while(q!=NULL) {
            struct Node *newNode = createNode();
            newNode->coeff = p->coeff*q->coeff;
            newNode->expo = p->expo+q->expo;
            if(rhead == NULL) {
                rhead = newNode;
                r = rhead;
            }
            else{
                r->link = newNode;
                r = newNode;
            }
            q=q->link;
        }
        q=qhead;
        p = p->link;
    }
    
    p =rhead;
    while(p!=NULL){
        prev = p;
        q= p->link;
        while(q!=NULL) {
            if(p->expo == q->expo) {
                p->coeff = p->coeff + q->coeff;
                prev->link = q->link;
                free(q);
                q = prev->link;
            }
            else{
                prev=q;
                q = q->link;
            }
        }
        p=p->link;
    }
    
    return rhead;
}

struct Node *add(struct Node *phead,struct Node *qhead){
    struct Node *p,*q,*rhead=NULL,*r,*prev;
    p=phead;
    q=qhead;
    r=rhead;
    
    while(p!=NULL && q!=NULL){
        struct Node *newNode = createNode();
        if(p->expo == q->expo) {
            newNode->coeff = p->coeff+q->coeff;
            newNode->expo= p->expo;
            p=p->link;
            q=q->link;
        }
        else if(p->expo >q->expo) {
            newNode->coeff = p->coeff;
            newNode->expo= p->expo;
            p=p->link;
        }
        else {
            newNode->coeff = q->coeff;
            newNode->expo= q->expo;
            q=q->link;
        }
        
        if (rhead == NULL) {
            rhead =newNode;
            r=rhead;
        }
        else{
            r->link = newNode;
            r = newNode;
        }
    }
    
    while(p!=NULL){
        struct Node *newNode = createNode();
        newNode->coeff = p->coeff;
        newNode->expo= p->expo;
        p=p->link;
        if (rhead == NULL) {
            rhead =newNode;
            r=rhead;
        }
        else{
            r->link = newNode;
            r = newNode;
        }
    }
    while(q!=NULL) {
        struct Node *newNode = createNode();
        newNode->coeff = q->coeff;
        newNode->expo= q->expo;
        q=q->link;
        if (rhead == NULL) {
            rhead =newNode;
            r=rhead;
        }
        else{
            r->link = newNode;
            r = newNode;
        }
    }
    return rhead;
}

int main(){
    struct Node *phead, *p, *qhead,*q, *rhead=NULL, *r;
    p = readPoly();
    q = readPoly();
    r = add(p,q);
    //r = multiply(p,q);
    display(p);
    display(q);
    display(r);

    return 0;
}
