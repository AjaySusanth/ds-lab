#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int hashT[SIZE]; // Array to represent the hash table

// Function to initialize the hash table
void inhashT() {
    for (int i = 0; i < SIZE; i++) {
        hashT[i] = -1; // -1 indicates an empty slot
    }
}

// Primary hash function
int hashFnt(int key) {
    return key % SIZE;
}

// Secondary hash function (must not be zero)
int secondHashFnt(int key) {
    return 7 - (key % 7); // Example of a secondary hash function
}

// Function to insert an element using double hashing
void insert(int key) {
    int index = hashFnt(key);
    int originalIndex = index;
    int stepSize = secondHashFnt(key);
    int i = 0;

    // Probe using double hashing until an empty slot is found or the table is full
    while (hashT[index] != -1 && hashT[index] != key) {
        i++;
        index = (originalIndex + stepSize * i) % SIZE;
        if (i >= SIZE) { // Ensure we don't loop indefinitely
            printf("Hash table is full. Could not insert key %d\n", key);
            return;
        }
    }

    if (hashT[index] == -1) {
        hashT[index] = key;
        printf("Inserted key %d at index %d\n", key, index);
    } else {
        printf("Key %d already exists at index %d\n", key, index);
    }
}

// Function to display the hash table
void display() {
    printf("HASH TABLE\n");
    for (int i = 0; i < SIZE; i++) {
        if (hashT[i] == -1) {
            printf("Index %d: NULL\n", i);
        } else {
            printf("Index %d: %d\n", i, hashT[i]);
        }
    }
}

int main() {
    // Initialize the hash table
    inhashT();

    // Insert elements
    insert(5);
    insert(2);
    insert(15);
    insert(25);
    insert(35);
    insert(45);

    // Display the hash table
    display();

    return 0;
}
