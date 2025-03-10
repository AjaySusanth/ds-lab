#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node *link;
};

struct Node *head = NULL;

void display() {
    if (head == NULL) {
        printf("List empty\n");
        return;
    }
    
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%i\t", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

void insert_end(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while (temp->link != NULL)
        temp = temp->link;
    temp->link = newNode;
}

// Helper function to get the last node of the list
struct Node* getLastNode(struct Node *node) {
    while (node != NULL && node->link != NULL) {
        node = node->link;
    }
    return node;
}

// Partition function for Quick Sort
struct Node* partition(struct Node *low, struct Node *high) {
    int pivot = high->data;
    struct Node *i = low->link;  // i is one node ahead of low initially
    struct Node *j = low;
    
    while (j != high) {
        if (j->data <= pivot) {
            i = (i == NULL) ? low : i->link;  // Move i if necessary
            int temp = i->data;
            i->data = j->data;
            j->data = temp;
        }
        j = j->link;
    }
    
    int temp = i->data;
    i->data = high->data;
    high->data = temp;
    
    return i;
}

// QuickSort recursive function
void quickSort(struct Node *low, struct Node *high) {
    if (low != NULL && high != NULL && low != high && low != high->link) {
        struct Node *pivot = partition(low, high);
        
        // Recursively sort the left and right sublists
        quickSort(low, pivot);
        quickSort(pivot->link, high);
    }
}

// Binary Search for sorted linked list
void binarySearch(int data) {
    struct Node *start = head, *end = NULL;
    
    while (start != end) {
        struct Node *slow = start, *fast = start;
        
        // Find the middle of the list
        while (fast != end && fast->link != end) {
            slow = slow->link;
            fast = fast->link->link;
        }
        
        struct Node *mid = slow;
        
        // Check if the middle element is the target
        if (mid->data == data) {
            printf("Element %d found\n", data);
            return;
        }
        
        // Narrow the search range
        if (mid->data > data) {
            end = mid;
        } else {
            start = mid->link;
        }
    }
    
    printf("Element %d not found\n", data);
}

int main() {
    insert_end(2);
    insert_end(10);
    insert_end(25);
    insert_end(3);
    insert_end(1);
    insert_end(11);
    
    printf("Original list: ");
    display();
    
    // Get the last node to be used in quickSort range
    struct Node *last = getLastNode(head);
    
    // Perform QuickSort
    quickSort(head, last);
    
    printf("Sorted list: ");
    display();
    
    binarySearch(10);
    binarySearch(5);
    
    return 0;
}
