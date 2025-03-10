#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    int data;
    struct Node *link;
};

struct Node *hashT[SIZE];

int hashFnt(int key) {
    return key % SIZE;
}

void inhashT() {
    for(int i=0;i<SIZE;i++)
        hashT[i] = NULL;
}



void insert_chaining(int key) {
    int index = hashFnt(key);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->link = NULL;
    if(hashT[index] == NULL) 
        hashT[index] = newNode;
    else {
        struct Node *temp = hashT[index];
        while(temp->link!=NULL)
            temp = temp->link;
        temp->link = newNode;
    }
}

void display_chain() {
    printf("HASH TABLE\n");
    for(int i=0;i<SIZE;i++) {
        printf("Index: %i: ",i);
        if(hashT[i] == NULL) 
            printf("NULL\n");
        else {
            struct Node *temp = hashT[i];
            while(temp!=NULL){
                printf("%i\t->\t",temp->data);
                temp = temp->link;
            }
            printf("NULL\n");
        }
    } 
}

int main() {
    insert(5);
    insert(2);
    insert(15);
    display();
    return 0;
}
