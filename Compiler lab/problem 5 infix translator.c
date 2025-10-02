#include <stdio.h>
#include <string.h>

#define MAX 100

int top;
char stack[MAX];

int isEmpty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

// Pop element from stack
char pop()
{
    char value = stack[top];
    top--;
    return value;
}

// Push element onto stack
void push(char item)
{
    top++;
    stack[top] = item;
}

// Get the precedence of an operator
int precedence(char op)
{
    if(op == '+' || op == '-')
        return 1;
    if(op == '*' || op == '/')
        return 2;
    if(op == '^')
        return 3;
    return 0;
}

// Convert infix expression to postfix using SDT
void infixToPostfix(char *exp, int len)
{
    // Set top of the stack
    top = -1;

    int i, k = 0;
    char postfix[MAX];
    for(i = 0; i < len; i++)
    {
        // If the character is an operand, add it to the output
        if((exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z') || (exp[i] >= '0' && exp[i] <= '9'))
        {
            while((exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'Z') || (exp[i] >= '0' && exp[i] <= '9'))
                postfix[k++] = exp[i++];

            i--;
        }

        // If the character is '(', push it onto stack
        else if(exp[i] == '(')
            push(exp[i]);

        // If the character is ')', pop and output from the stack until '(' is encountered
        else if(exp[i] == ')')
        {
            while(stack[top] != '(')
                postfix[k++] = pop();

            pop(); // Pop '('
        }

        // If the character is an operator
        else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
        {
            while(top != -1 && precedence(stack[top]) >= precedence(exp[i]))
                postfix[k++] = pop();

            push(exp[i]);
        }

        // If the character is a semicolon, end of an expression
        else if(exp[i] == ';')
        {
            while(top != -1)
                postfix[k++] = pop();

            postfix[k] = '\0';  // Null terminate the postfix string
            printf("Postfix: %s\n", postfix);
            k = 0;  // Reset for the next expression
        }
    }
}

int main() {
    char input[MAX];

    // Take input from the user
    printf("Enter the infix expression(s) terminated by semicolons:\n");
    fgets(input, sizeof(input), stdin);

    int len = strlen(input) -  1;

    // Translate from infix to postfix
    infixToPostfix(input, len);

    return 0;
}
