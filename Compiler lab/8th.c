#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX];
char stack[MAX][MAX];
int top = -1, pos = 0, len;

// Push and pop
void push(char *s)
{
    strcpy(stack[++top], s);
}
void pop()
{
    top--;
}

// Display stack, remaining input, and action
void show(char *action)
{
    printf("Stack: $");
    for(int i = 0; i <= top; i++)
        printf("%s", stack[i]);
    printf("%-15s", ""); // spacing
    printf("Input: ");
    for(int i = pos; i < len; i++)
    printf("%c", input[i]);
    printf("$%-10s", ""); // spacing
    printf("Action: %s\n", action);
}

// Try to reduce stack based on grammar
int reduce()
{
    if(top >= 0 && strcmp(stack[top], "a") == 0)
    {
        pop();
        push("E");
        show("E->a");
        return 1;
    }
    if(top >= 2 && strcmp(stack[top-2], "E")==0 && strcmp(stack[top-1], "+")==0 && strcmp(stack[top], "E")==0)
    {
        pop();
        pop();
        pop();
        push("E");
        show("E->E+E");
        return 1;
    }
    if(top >= 2 && strcmp(stack[top-2], "E")==0 && strcmp(stack[top-1], "*")==0 && strcmp(stack[top], "E")==0)
    {
        pop();
        pop();
        pop();
        push("E");
        show("E->E*E");
        return 1;
    }
    if(top >= 2 && strcmp(stack[top-2], "(")==0 && strcmp(stack[top-1], "E")==0 && strcmp(stack[top], ")")==0)
    {
        pop();
        pop();
        pop();
        push("E");
        show("E->(E)");
        return 1;
    }
    return 0;
}

// Shift-reduce parsing
void parse()
{
    printf("Stack: $%-15sInput: %s$%-10sAction: -\n", "", input, "");
    while(pos < len)
    {
        if(input[pos] == ' ')
        {
            pos++;
            continue;
        }

        char temp[2] = {input[pos], 0};
        push(temp);
        show("shift");

        while(reduce()) {}
        pos++;
    }
    while(reduce()) {}
}

int main()
{
    printf("Grammar:\nE->E+E\nE->E*E\nE->(E)\nE->a\n");
    printf("Enter input string: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0;
    len = strlen(input);

    printf("\nParsing steps:\n\n");
    parse();

    return 0;
}
