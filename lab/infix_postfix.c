#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
char stack[20],infix[20];
int top=-1;

void push(char x){
    stack[++top] = x;
}
char pop() {
    if(top ==-1) return -1;
    return stack[top--];
}

int isOperator(char op) {
    if(op == '+' || op == '-' || op == '/' || op == '*' || op == '^') return 1;
    return 0;
}

int prio(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
            
        case '^':
            return 3;
    }
    return 0;
}

void infix_to_postfix(char infix[]) {
    int i=0,j=0;
    char x,e,postfix[20];
    
    while((e = infix[i++])!='\0') {
        if(isalnum(e)) postfix[j++] = e;
        else if (e == '(') push(e);
        else if (e == ')') {
            while((x=pop())!='(')
                postfix[j++] = x;
        }
        else {
            while(prio(e) <= prio(stack[top]))
                postfix[j++] = pop();
            push(e);
        }   
    }
    while(top!=-1)
        postfix[j++] = pop();
    postfix[j] = '\0';
    
    printf("Posfix exp: %s\n",postfix);
}

void evaluate() {
    char postfix1[20],str[20],e;
    int stack1[20],top=-1,i=0,op1,op2,result;
    
    printf("enter the postfix exp\n");
    scanf("%s",postfix1);
    
    for(int i=0;i<strlen(postfix1);i++) {
        e = postfix1[i];
        if(isdigit(e)) {
            str[0] = e;
            str[1] = '\0';
            stack1[++top] = atoi(str);
        }
        else {
            op2 =stack1[top--];
            op1 = stack1[top--];
            switch(e) {
                case '+': result  = op1+op2; break;
                case '-': result  = op1-op2; break;
                case '*': result  = op1*op2; break;
                case '/': result  = op1/op2; break;
                case '^': result  = pow(op1,op2); break;
            }
            stack1[++top] = result;
        }
    }
     printf("Eval: %i\n",stack1[top]);
    
}

int main() {
    // Write C code here
    printf("infix\n");
    scanf("%s",infix);
    infix_to_postfix(infix);
    evaluate();
    return 0;
}