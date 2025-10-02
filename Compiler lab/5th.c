#include <stdio.h>
#include <string.h>

#define MAX 100
char stack[MAX];
int top=-1;

void push(char c)
{
    stack[++top]=c;
}
char pop()
{
    return stack[top--];
}
int prec(char c)
{
    return (c=='+'||c=='-')?1:(c=='*'||c=='/')?2:(c=='^')?3:0;
}

void infixToPostfix(char *exp)
{
    char postfix[MAX];
    int k=0;
    for(int i=0; i<strlen(exp); i++)
    {
        char c=exp[i];
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))
        {
            while((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))
            {
                postfix[k++]=c;
                c=exp[++i];
            }
            i--;
        }
        else if(c=='(') push(c);
        else if(c==')')
        {
            while(stack[top]!='(') postfix[k++]=pop();
            pop();
        }
        else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
        {
            while(top!=-1 && prec(stack[top])>=prec(c)) postfix[k++]=pop();
            push(c);
        }
        else if(c==';')
        {
            while(top!=-1) postfix[k++]=pop();
            postfix[k]='\0';
            printf("Postfix: %s\n",postfix);
            k=0;
        }
    }
}

int main()
{
    char input[MAX];
    printf("Enter infix expression(s) terminated by semicolons:\n");
    fgets(input,MAX,stdin);
    input[strcspn(input,"\n")]=0;
    infixToPostfix(input);
}

