#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int hashT[SIZE];

int hashFnt(int key) {
    return key % SIZE;
}

void inhashT() {
    for(int i=0;i<SIZE;i++)
        hashT[i] = -1;
}

void insert(int key) {
    int index = hashFnt(key);
    int i=0;
    int originalIndex = index;
    
    while(hashT[index]!=-1 && hashT[index]!=key) {
        i++;
        index = (originalIndex + i) % SIZE;
        if(index == originalIndex) {
            printf("Hash table is full\n", key);
            return;
        }
    }
    
    if(hashT[index] == -1) 
        hashT[index] = key;
    else {
        printf("Key already exists\n");
    }
}

void display() {
    printf("HASH TABLE\n");
    for(int i=0;i<SIZE;i++) {
        printf("Index: %i: ",i);
        if(hashT[i] == -1) 
            printf("NULL\n");
        else {
            printf("%i\n",hashT[i]);    
        }
    }
}
 


int main() {
    inhashT();
    insert(5);
    insert(8);
    insert(18);
    insert(28);
    insert(38);
    insert(15);
    insert(1);
    insert(11);
    insert(13);
    insert(23);
    insert(10);
    display();
    return 0;
}



