#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
    struct Employee *next;
};

struct Employee* createEmployee(int id, char* name, float salary) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    newEmployee->salary = salary;
    newEmployee->next = NULL;
    return newEmployee;
}

struct Employee* insertEmployee(struct Employee* head, int id, char* name, float salary) {
    struct Employee* newEmployee = createEmployee(id, name, salary);
    if (head == NULL) {
        return newEmployee;
    }
    struct Employee* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newEmployee;
    return head;
}


void displayEmployees(struct Employee* head) {
    if (head == NULL) {
        printf("No employees in the list.\n");
        return;
    }
    struct Employee* temp = head;
    printf("ID\tName\t\tSalary\n");
    printf("---------------------------------\n");
    while (temp != NULL) {
        printf("%d\t%s\t\t%.2f\n", temp->id, temp->name, temp->salary);
        temp = temp->next;
    }
    printf("\n");
}

struct Employee* deleteEmployee(struct Employee* head, int id) {
    struct Employee* temp = head;
    struct Employee* prev = NULL;
    
    if (temp != NULL && temp->id == id) {
        head = temp->next; // Changed head
        free(temp); // free old head
        return head;
    }
    
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Employee with ID %d not found.\n", id);
        return head;
    }

    prev->next = temp->next;
    free(temp);
    return head;
}

struct Node *binarySearch(struct Node *head,int id) {
    struct Node *mid=NULL,*start = head, *end = NULL,*slow=head,*fast = head;
    
    while(fast!=NULL && fast->link!=NULL) {
        slow = slow->link;
        fast = fast->link->link;
    }
    mid = slow;
    
    if(mid->id == id)
        return mid;
    
    while(end ==NULL || end!=start) {
        if(mid->id == id)
            return mid;
        if(mid->id > id) {
            end = mid;
        }
        else {
            mid = mid->link;
        }
    }
    return NULL;
}