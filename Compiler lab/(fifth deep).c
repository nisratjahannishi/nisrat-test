#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c)
{
    stack[++top] = c;
}
char pop()
{
    return stack[top--];
}
int isEmpty()
{
    return top == -1;
}

int precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

void infixToPostfix(char *exp)
{
    char postfix[MAX];
    int k = 0;

    for (int i = 0; exp[i]; i++)
    {
        char ch = exp[i];

        if (isalnum(ch))
        {
            // Handle multi-digit numbers and variables
            while (isalnum(exp[i]))
            {
                postfix[k++] = exp[i++];
            }
            postfix[k++] = ' ';  // Add space after each operand
            i--;
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (!isEmpty() && stack[top] != '(')
            {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            pop();  // Remove '('
        }
        else if (precedence(ch) > 0)    // If it's an operator
        {
            while (!isEmpty() && precedence(stack[top]) >= precedence(ch))
            {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            push(ch);
        }
        else if (ch == ';')
        {
            while (!isEmpty())
            {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            postfix[k-1] = '\0';  // Remove last space and terminate
            printf("Postfix: %s\n", postfix);
            k = 0;  // Reset for next expression
        }
    }
}

int main()
{
    char input[MAX];

    printf("Enter infix expressions (end with ;):\n");
    fgets(input, sizeof(input), stdin);

    infixToPostfix(input);

    return 0;
}
