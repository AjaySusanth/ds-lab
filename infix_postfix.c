#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char infix[20];
char postfix[20],eval_postfix[20];
char stack[20];
int stack1[20];
int top=-1,top1=-1;

int precedence (char c) {
    switch(c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
}

void infix_to_postfix () {
    int i=0,j=0;
    char x,y;
    while (infix[i]!='\0') {
        if(isdigit(infix[i]))
            postfix[j++] = infix[i];
        else if(infix[i] == '(')
            stack[++top] = infix[i];
        else if(infix[i] == ')')
        {
            while (stack[top]!='(')
                postfix[j++] = stack[top--];
            top--;
        }
        else {
            x=infix[i];
            y=stack[top];
            if (top == -1 || y=='(' || precedence(y)<precedence(x))
                stack[++top] = infix[i];
            else {
                while (y!='(' && top!=-1 && precedence(x)<=precedence(y)) {
                    postfix[j++] = stack[top--];
                    y = stack[top];
                }
                stack[++top] = x;
            }
        }
        i++;
    }
    
    while (top!=-1)
        postfix[j++] = stack[top--];
    postfix[j] = '\0';
    
    printf("Postfix expression is %s\n",postfix);
}

void evaluate() {
    int i, op1,op2,result;
    char str[10];
    for(int i=0;i<strlen(eval_postfix);i++) {
        if(isdigit(eval_postfix[i])) {
            str[0] = eval_postfix[i];
            str[1] = '\0';
            stack1[++top1] = atoi(str);
        }
        else {
            op2 = stack1[top1--];
            op1 = stack1[top1--];
            switch(eval_postfix[i]) {
                case '+' : 
                    result = op1+op2;
                    break;
                case '-':
                    result = op1-op2;
                    break;
                case '*':
                    result = op1*op2;
                    break;
                case '/':
                    result = op1/op2;
                    break;
                case '^':
                    result = pow(op1,op2);
                    break;
            }
            stack1[++top1] = result;
        }

    }
    printf("Result = %d\n",stack1[0]);
    
    
}

int main() {
    int menu=0,choice;
    while (menu==0) {
        printf("1. Infix to postfix conversion  2.Postfix Evaluation 3.Exit\n");
        scanf("%i",&choice);
        switch(choice) {
            case 1:
                printf("Enter the expression\n");
                scanf("%s",infix);
                infix_to_postfix();
                break;
            case 2:
                printf("Enter the postfix expression\n");
                scanf("%s",eval_postfix);
                evaluate();
                break;
            case 3:
                menu=1;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}