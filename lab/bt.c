#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};


//Insertion of Elts:
//NT: Recursion leap of faith => Create the logic for top tree, subtrees will be handled by recursion
struct Node *createTree() {
    int data;

    printf("Enter data:\n");
    scanf("%i",&data);
    if(data ==-1) return NULL;
    struct Node *root = (struct Node*)malloc(sizeof(struct Node));
    root->data = data;
    
    printf("Enter left child for %i\n",root->data);
    root->left = createTree();

    printf("Enter right child for %i\n",root->data);
    root->right = createTree();
    
    return root;
}


// BT Traversals
void inOrder(struct Node *root) {
    if (root == NULL) return;
    
    inOrder(root->left);
    printf("%i",root->data);
    inOrder(root->right);
    
}

void preOrder(struct Node *root) {
    if (root == NULL) return;
    
    printf("%i",root->data);
    preOrder(root->left);
    preOrder(root->right);
    
}

void postOrder(struct Node *root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%i",root->data);
}


// Height of BT
int height(struct Node *root) {
    if(root == NULL) return 0;
    return (height(root->left) > height(root->right) ? height(root->left) : height(root->right)) + 1;
}

// Diameter of BT => distance btw leaf nodes
int diameter(struct Node *root) {
    if(root == NULL) return 0;
    
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    
    int maxDiameter = leftHeight+rightHeight+1;
    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);
    
    return (maxDiameter > leftDiameter && maxDiameter > rightDiameter) ? maxDiameter : (leftDiameter > rightDiameter) ? leftDiameter : rightDiameter;
}

// Size => No.of nodes
int size(struct Node *root) {
    if (root == NULL) return 0;
    return (size(root->left)+size(root->right))+1;
}

int findMax(struct Node *root) {
    if(root == NULL) return INT_MIN;
    
    int leftMax =findMax(root->left);
    int rightMax = findMax(root->right);
    
    int maxVal = root->data;
    
    if(leftMax > maxVal) maxVal = leftMax;
    if(rightMax > maxVal) maxVal = rightMax;
    
    return maxVal;
}

int findMin(struct Node *root) {
    if (root == NULL)
        return INT_MAX;

    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);

    int minVal = root->data;
    if (leftMin < minVal)
        minVal = leftMin;
    if (rightMin < minVal)
        minVal = rightMin;

    return minVal;
}


// LEVEL ORDER TRAVERSAL

struct QueueNode {
    struct Node *treeNode;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front,*rear;
};

struct Queue *createQueue() {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

void enq(struct Queue *q,struct Node *treeNode) {
    struct QueueNode *newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if(q->front == NULL) {
        q->rear = q->front = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

struct Node* dq (struct Queue *q) {
    if(q->front == NULL) return NULL;

    struct QueueNode *temp = q->front;
    struct Node *treeNode = temp->treeNode;
    q->front = q->front->next;
    if(q->front ==NULL) q->rear = NULL;

    free(temp);
    return treeNode;

}

int isQEmpty(struct Queue* q){
    return q->front == NULL;
}

void levelOrder(struct Node* root) {
    if(root == NULL) return;

    struct Queue *q = createQueue();
    enq(q,root);
    while(!isQEmpty(q)){
        struct Node *curr = dq(q);
        printf("%d ", curr->data);

        if(curr->left!=NULL) enq(q,curr->left);
        if(curr->right!=NULL ) enq(q,curr->right);
    }
    printf("\n");
}

// Prints levels by line
void levelOrderLineByLine(struct Node* root) {
    if(root == NULL) return;

    struct Queue *q = createQueue();
    enq(q,root);

    while(!isQEmpty(q)) {
        int levelSize = 0;
        struct QueueNode *temp = q->front;

        while(temp!=NULL) {
            levelSize++;
            temp = temp->next;
        }

        for(int i=0;i<levelSize;i++) {
            struct Node *curr = dq(q);
            printf("%d ", curr->data);

            if(curr->left!=NULL) enq(q,curr->left);
            if(curr->right!=NULL ) enq(q,curr->right);
        }
        printf("\n");

    }
}




int main() {
    // Write C code here
    struct Node *root = (struct Node*)malloc(sizeof(struct Node));
    root = createTree();
    printf("%i\n",height(root));
    printf("%i\n",size(root));
    printf("%i\n",findMax(root));
    printf("%i\n",findMin(root));
    levelOrder(root);
    levelOrderLineByLine(root);
    return 0;
}