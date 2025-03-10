#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node *left,*right;
};

struct Node *root =NULL;

void insert(int data) {
    struct Node *newNode, *ptr, *parent;
    if(root == NULL) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        root = newNode;
        return;
    }
    ptr = root;
        while(ptr!=NULL ) {
            parent = ptr;
            if(ptr->data == data) {
                printf("item exists\n");
                return;
            }
            else if(data < ptr->data) {
                ptr = ptr->left;
            }
            else {
                ptr = ptr->right;
            }   
        }
        
        if(ptr == NULL) {
            newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->data = data;
            newNode->left = newNode->right = NULL;
            if(data > parent->data) parent->right = newNode;
            else parent->left = newNode;
        }
}

struct Node *inOrderPredecessor(struct Node *root) {
    root = root->left;
    while(root->right !=NULL) root = root->right;
    return root;
}

struct Node *deleteNode(struct Node *root,int data) {
    if(root == NULL)return NULL;
    if(root->left == NULL && root->right ==NULL) {
        free(root);
        return NULL;
    }
    struct Node *iPre;
    if(data < root->data) root->left = deleteNode(root->left,data);
    else if(data > root->data) root->right = deleteNode(root->right,data);
    
    else {
        iPre = inOrderPredecessor(root);
        root->data = iPre->data;
        root->left = deleteNode(root->left,iPre->data);
    }
    
    return root;
}

int findMax(struct Node *root) {
    if(root == NULL) return INT_MIN;
    
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    
    return (root->data > leftMax && root->data > rightMax) ? root->data : (leftMax > rightMax ? leftMax : rightMax);
}

int findMin(struct Node *root) {
    if(root == NULL) return INT_MAX;
    
    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);
    
    return (root->data < leftMin && root->data < rightMin) ? root->data : (leftMin < rightMin ? leftMin : rightMin);
}

int isBst(struct Node *root) {
    if(root==NULL) return 1;
    
    if(root!=NULL && findMax(root->left) >= root->data)
        return 0;
    if(root!=NULL && findMin(root->right) <= root->data)
        return 0;
        
    return isBst(root->left) && isBst(root->right);
}

int isFullBinaryTree(struct Node* root) {
    // A NULL tree is a full binary tree
    if (root == NULL)
        return 1;

    // Check if the node is a leaf node
    if (root->left == NULL && root->right == NULL)
        return 1;

    // Check if both left and right children exist
    if (root->left != NULL && root->right != NULL)
        return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);

    // If none of the above cases, it is not a full binary tree
    return 0;
}


// INORDER OF BST GIVES ASCENDING ORDER
void inOrder(struct Node *root) {
    if (root == NULL) return;
    
    inOrder(root->left);
    printf("%i\t",root->data);
    inOrder(root->right);
    
}

int main() {
    insert(10);
    insert(15);
    insert(5);
    insert(12);
    inOrder(root);
    printf("\n");
    root = deleteNode(root,5);
    inOrder(root);
    printf("\n%i",isBst(root));
    return 0;
}