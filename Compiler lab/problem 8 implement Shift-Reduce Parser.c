#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX];
char stack[MAX][MAX]; // Stack for parsing
int top = -1, pos = 0, len;

// Function to push an element onto the stack
void push(char *str) { strcpy(stack[++top], str); }

// Function to pop an element from the stack
void pop() { top--; }

void display_rem_input(int i, char *action)
{
    printf(" \t Input: ");
    while(i < len)
        printf("%c", input[i++]);

    printf("$ \t Action: %s\n", action);
}

// Function to display the current stack
void displayStack()
{
    int i;
    printf("Stack: $");
    for(i = 0; i <= top; i++)
        printf("%s ", stack[i]);
}

// Function to check and reduce the stack based on grammar
int checkAndReduce()
{
    // Check for the pattern 'a'
    if(top >= 0 && strcmp(stack[top], "a") == 0)
    {
        pop();
        push("E");  // Replace 'a' with 'E'
        displayStack();
        display_rem_input(pos + 1, "reduce by E -> a");
        return 1;
    }

    // Check for the pattern 'E + E'
    else if(top >= 2 && strcmp(stack[top], "E") == 0 && strcmp(stack[top - 1], "+") == 0 && strcmp(stack[top - 2], "E") == 0)
    {
        pop(); pop(); pop();
        push("E");  // Replace 'E + E' with 'E'
        displayStack();
        display_rem_input(pos + 1, "reduce by E -> E + E");
        return 1;
    }

    // Check for the pattern 'E * E'
    else if(top >= 2 && strcmp(stack[top], "E") == 0 && strcmp(stack[top - 1], "*") == 0 && strcmp(stack[top - 2], "E") == 0)
    {
        pop(); pop(); pop();
        push("E");  // Replace 'E * E' with 'E'
        displayStack();
        display_rem_input(pos + 1, "reduce by E -> E * E");
        return 1;
    }

    // Check for the pattern '( E )'
    else if(top >= 2 && strcmp(stack[top], ")") == 0 && strcmp(stack[top - 1], "E") == 0 && strcmp(stack[top - 2], "(") == 0)
    {
        pop(); pop(); pop();
        push("E");  // Replace '( E )' with 'E'
        displayStack();
        display_rem_input(pos + 1, "reduce by E -> ( E )");
        return 1;
    }

    return 0;  // No reduction possible
}

// Main parsing function
void parse()
{
    printf("Stack: $ \t Input: %s$ \t Action: -\n", input);

    while(pos < len)
    {
        if(input[pos] == ' ')
        {
            pos++;
            continue;
        }

        // Shift operation
        char temp[2];
        temp[0] = input[pos];
        temp[1] = '\0';
        push(temp);
        displayStack();
        display_rem_input(pos + 1, "shift");

        // Try to reduce after every shift
        while(checkAndReduce()) {}

        pos++;
    }

    // Final reductions
    while(checkAndReduce()) {}
}

int main() {
    printf("Grammar: \nE -> E + E\nE -> E * E\nE -> (E)\nE -> a\n");
    printf("Enter the input string: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline
    len = strlen(input);
    printf("\nConfigurations of a shift-reduce parser on input: %s\n\n", input);
    parse();

    return 0;
}
