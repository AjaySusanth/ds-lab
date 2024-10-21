#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
};
char stack[100];
int top = -1;
char push(char x)
{
    stack[++top] = x;
}
char pop()
{
    if (top == -1)
    {
        return -1;
    }
    else
        return stack[top--];
}
struct Node *createNode(char data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    else
        return 0;
}
int prio(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}
void infixTopostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;
    char x, e;
    while ((e = infix[i++]) != '\0')
    {
        if (isalnum(e))
        {
            postfix[j++] = e;
        }
        else if (e == '(')
        {
            push(e);
        }
        else if (e == ')')
        {
            while ((x = pop()) != '(')
            {
                postfix[j++] = x;
            }
        }
        else
        {
            while (prio(stack[top]) >= prio(e))
                postfix[j++] = pop();
            push(e);
        }
    }
    while (top != -1)
        postfix[j++] = pop();
    postfix[j] = '\0';
}
struct Node *buildExpressionTree(char postfix[])
{
    struct Node *stack[100];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++)
    {
        struct Node *node = createNode(postfix[i]);
        if (isalnum(postfix[i]))
        {
            stack[++top] = node;
        }
        else if (isOperator(postfix[i]))
        {
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    return stack[top];
}
void inOrderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%c", root->data);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        printf("%c", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}
void postOrderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%c", root->data);
    }
}
int main()
{
    char infix[100], postfix[100];
    printf("Enter the expression in infix form:");
    scanf("%s", infix);

    infixTopostfix(infix, postfix);

    struct Node *root = buildExpressionTree(postfix);
    printf("In-order traversal:");
    inOrderTraversal(root);
    printf("\n");
    printf("Pre-order traversal:");
    preOrderTraversal(root);
    printf("\n");
    printf("Post-order traversal:");
    postOrderTraversal(root);
    printf("\n");
    return 0;
}
