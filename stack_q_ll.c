#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *link;
};

struct node *top,*f,*r;

void stack_display() {
    struct node *ptr;
    if(top == NULL)
        printf("Stack empty\n");
    else {
        ptr=top;
        printf("Stack elements\n");
        while(ptr!=NULL)
        {
            printf("%i\t",ptr->data);
            ptr = ptr->link;
        }
        printf("\n");
    }
}
void stack_push(int item) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = item;
    newNode->link = NULL;
    if(top == NULL)
        top = newNode;
    else {
        newNode->link = top;
        top = newNode;
    }
    
    stack_display();
}

int stack_pop() {
    int data;
    
    if(top == NULL) {
        printf("Stack empty\n");
        return 0;
    }
    else {
        struct node *ptr;
        ptr = top;
        printf("Popped element: %i\n",top->data);
        data = top->data;
        top = top->link;
        free(ptr);
        stack_display();
        return data;
    }
}

void qdisplay() {
    struct node *ptr;
    if(f==NULL)
        printf("Queue empty\n");
    else {
        ptr =f;
        printf("Queue elements\n");
        while(ptr!=NULL) {
            printf("%i\t",ptr->data);
            ptr = ptr->link;
            
        }
        printf("\n");
    }
}


void enqueue(int item) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = item;
    newNode->link = NULL;
    if(f==NULL) {
        f=newNode;
        r=newNode;
    }
    else {
        r->link = newNode;
        r=r->link;
        
    }
    
    qdisplay();
}

int dequeue () {
    int item;
    struct node *ptr;
    if(f==NULL) {
        printf("Queue empty\n");
        return 0;
    }
    else if(f->link==NULL){
        ptr = f;
        printf("Deleted item: %i\n",f->data);
        item = f->data;
        f=NULL;
        r=NULL;
        free(ptr);
        return item;
    }
    else {
        ptr=f;
        printf("Deleted item: %i\n",f->data);
        item = f->data;
        f=ptr->link;
        free(ptr);
        return item;
    }
}


int main () {
    int menu1=0,menu2,ch1,ch2,elt;
    
    while(menu1==0) {
        printf("1.Stack 2.Queue 3.Exit\n");
        scanf("%i",&ch1);
        switch(ch1) {
            case 1:
                menu2=0;
                while (menu2==0) {
                    printf("1.Push 2.Pop 3.Display 4.Main menu\n");
                    scanf("%i",&ch2);
                    switch(ch2) {
                        case 1:
                            printf("Enter the elt to push\n");
                            scanf("%i",&elt);
                            stack_push(elt);
                            break;
                        case 2:
                            stack_pop();
                            break;
                        case 3:
                            stack_display();
                            break;
                        case 4:
                            menu2=1;
                            break;
                        default:printf("Invalid choice\n");
                    }
                }
                break;
            case 2:
                menu2=0;
                while (menu2==0) {
                    printf("1.Enqueue 2.Dequeue 3.Display 4.Main menu\n");
                    scanf("%i",&ch2);
                    switch(ch2) {
                        case 1:
                            printf("Enter the elt to insert\n");
                            scanf("%i",&elt);
                            enqueue(elt);
                            break;
                        case 2:
                            dequeue();
                            break;
                        case 3:
                            qdisplay();
                            break;
                        case 4:
                            menu2=1;
                            break;
                        default:printf("Invalid choice\n");
                        
                    }
                }
                break;
                
            case 3:
                menu1=1;
                break;
            
            default: printf("Invalid choice\n");
                
                
        }
    } 
    
    return 0;
}

