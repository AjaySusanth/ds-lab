#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MAX_SIZE 100

struct PriorityQueue {
    int data;
    int priority;
} pq[MAX];

int pqSize = 0; 
int n;         

int queue[MAX_SIZE]; 
int front = -1;
int rear = -1;

// Priority Queue Operations
void insertPriorityQueue() {
    if (pqSize == MAX) {
        printf("Priority Queue Overflow\n");
    } else {
        int item, priority;
        printf("Enter element to insert: ");
        scanf("%d", &item);
        printf("Enter priority: ");
        scanf("%d", &priority);
        pq[pqSize].data = item;
        pq[pqSize].priority = priority;
        pqSize++;
    }
}

void deletePriorityQueue() {
    if (pqSize == 0) {
        printf("Priority Queue Underflow\n");
    } else {
        int highestPriorityIndex = 0;
        for (int i = 1; i < pqSize; i++) {
            if (pq[i].priority > pq[highestPriorityIndex].priority) {
                highestPriorityIndex = i;
            }
        }
        printf("Deleted element: %d\n", pq[highestPriorityIndex].data);
        for (int i = highestPriorityIndex; i < pqSize - 1; i++) {
            pq[i] = pq[i + 1];
        }
        pqSize--;
    }
}

void displayPriorityQueue() {
    if (pqSize == 0) {
        printf("Priority Queue is empty\n");
    } else {
        printf("Priority Queue elements are:\n");
        for (int i = 0; i < pqSize; i++) {
            printf("Element: %d, Priority: %d\n", pq[i].data, pq[i].priority);
        }
    }
}

// Queue Operations
void push(int x) {
    if (rear == n - 1) {
        printf("Queue is full\n");
    } else {
        if (front == -1 && rear == -1) {
            front = rear = 0;
        } else {
            rear++;
        }
        queue[rear] = x;
    }
}

void pop() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else if (front == rear) {
        printf("Popped item is: %d\n", queue[front]);
        front = rear = -1;
    } else {
        printf("Popped item is: %d\n", queue[front]);
        front++;
    }
}

void display() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("The elements are:\n");
        for (int i = front; i <= rear; i++) {
            printf("%d\t", queue[i]);
        }
        printf("\n");
    }
}

// Circular Queue Operations
void enqueue(int x) {
    if ((rear + 1) % n == front) {
        printf("Circular Queue is full\n");
    } else if (front == -1 && rear == -1) {
        front = rear = 0;
        queue[rear] = x;
    } else {
        rear = (rear + 1) % n;
        queue[rear] = x;
    }
}

void dequeue() {
    if (front == -1 && rear == -1) {
        printf("Circular Queue is empty\n");
    } else if (front == rear) {
        printf("Dequeued item is: %d\n", queue[front]);
        front = rear = -1;
    } else {
        printf("Dequeued item is: %d\n", queue[front]);
        front = (front + 1) % n;
    }
}

void displayCircularQueue() {
    if (front == -1 && rear == -1) {
        printf("Circular Queue is empty\n");
    } else {
        printf("The elements are:\n");
        if (front <= rear) {
            for (int i = front; i <= rear; i++) {
                printf("%d\t", queue[i]);
            }
        } else {
            for (int i = front; i < n; i++) {
                printf("%d\t", queue[i]);
            }
            for (int i = 0; i <= rear; i++) {
                printf("%d\t", queue[i]);
            }
        }
        printf("\n");
    }
}

int main() {
    int sw, e, ch, menu1 = 0, menu2 = 0;
    while (menu1 == 0) {
        printf("1. Queue  2. Circular Queue  3. Priority Queue  4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                menu2 = 0;
                printf("Enter the size of the queue: ");
                scanf("%d", &n);
                while (menu2 == 0) {
                    printf("1. Push  2. Pop  3. Display  4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &sw);
                    switch (sw) {
                        case 1:
                            printf("Enter the element to be inserted: ");
                            scanf("%d", &e);
                            push(e);
                            break;
                        case 2:
                            pop();
                            break;
                        case 3:
                            display();
                            break;
                        case 4:
                            menu2 = 1;
                            break;
                        default:
                            printf("Invalid choice\n");
                    }
                }
                break;

            case 2:
                menu2 = 0;
                printf("Enter the size of the queue: ");
                scanf("%d", &n);                
                while (menu2 == 0) {
                    printf("1. Enqueue  2. Dequeue  3. Display  4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &sw);
                    switch (sw) {
                        case 1:
                            printf("Enter the element to be inserted: ");
                            scanf("%d", &e);
                            enqueue(e);
                            break;
                        case 2:
                            dequeue();
                            break;
                        case 3:
                            displayCircularQueue();
                            break;
                        case 4:
                            menu2 = 1;
                            break;
                        default:
                            printf("Invalid choice\n");
                    }
                }
                break;

            case 3:
                menu2 = 0; 
                while (menu2 == 0) {
                    printf("1. Insert Element  2. Delete Highest Priority Element  3. Display  4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &sw);
                    switch (sw) {
                        case 1:
                            insertPriorityQueue();
                            break;
                        case 2:
                            deletePriorityQueue();
                            break;
                        case 3:
                            displayPriorityQueue();
                            break;
                        case 4:
                            menu2 = 1;
                            break;
                        default:
                            printf("Invalid choice\n");
                    }
                }
                break;

            case 4:
                menu1 = 1;
                break;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
