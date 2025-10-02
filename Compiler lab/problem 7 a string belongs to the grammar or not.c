#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 100

// Global variables
char input[MAX_LENGTH];
int position = 0;

// Function prototypes for our grammar rules
bool S();
bool A();
bool B();

// Helper function to get the current character
char curr_char()
{
    return input[position];
}

// Helper function to move to the next character
void nextPos()
{
    position++;
}

// B -> bB | ε
bool B()
{
    if(curr_char() == 'b')
    {
        nextPos();
        return B();
    }

    return true; // ε (epsilon) production
}

// A -> aA | ε
bool A()
{
    if(curr_char() == 'a')
    {
        nextPos();
        return A();
    }

    return true; // ε (epsilon) production
}

// S -> aAb | bBA
bool S()
{
    if(curr_char() == 'a')
    {
        nextPos();
        if(A() && curr_char() == 'b')
        {
            nextPos();
            return true;
        }
    }

    else if(curr_char() == 'b')
    {
        nextPos();
        return B() && A();
    }

    return false;
}

int main() {
    printf("Grammar: \nS -> aAb | bBA\nA -> aA | e\nB -> bB | e\n");
    printf("Enter a string to check: ");
    scanf("%s", input);

    position = 0; // Reset the position

    if(S() && curr_char() == '\0')
        printf("The string '%s' belongs to the grammar.\n", input);
    else
        printf("The string '%s' does not belong to the grammar.\n", input);

    return 0;
}
