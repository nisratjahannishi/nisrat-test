#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Global variables
char input[100];
int position = 0;

// Function prototypes for grammar rules
bool E();
bool E_prime();
bool T();
bool T_prime();
bool F();

// Helper function to get the current character
char curr_char() { return input[position]; }

// Helper function to move to the next character
void nextPos() { position++; }

// E → T E'
bool E()
{
    printf("E -> T E'\n");

    if(T() && E_prime())
        return true;
    else
        return false;
}

// E' → + T E' | ε
bool E_prime()
{
    if(curr_char() == '+')
    {
        printf("E' -> + T E'\n");
        nextPos();

        if(T() && E_prime())
            return true;
        else
            return false;
    }

    // E' → ε (epsilon)
    printf("E' -> e\n");
    return true;
}

// T → F T'
bool T()
{
    printf("T -> F T'\n");

    if(F() && T_prime())
        return true;
    else
        return false;
}

// T' → * F T' | ε
bool T_prime()
{
    if(curr_char() == '*')
    {
        printf("T' -> * F T'\n");
        nextPos();

        if(F() && T_prime())
            return true;
        else
            return false;
    }

    // T' → ε (epsilon)
    printf("T' -> e\n");
    return true;
}

// F → ( E ) | a
bool F()
{
    if(curr_char() == '(')
    {
        printf("F -> ( E )\n");
        nextPos();  // Move past '('

        if(E() && curr_char() == ')')
        {
            nextPos();  // Move past ')'
            return true;
        }

        else
            return false;  // Failed to match ')'
    }

    else if(curr_char() == 'a')
    {
        printf("F -> a\n");
        nextPos();  // Move past 'a'
        return true;
    }

    else
        return false;
}

void parse()
{
    printf("\nSteps: \n");

    // Start parsing from E (the start symbol)
    if(E() && curr_char() == '\0')
        printf("\nParsing successful!\n");
    else
        printf("\nParsing failed!\n");
}

int main()
{
    printf("Grammar: \nE -> T E'\nE' -> + T E' | e\nT -> F T'\nT' -> * F T' | e\nF -> ( E ) | a\n");
    printf("Enter the input string: ");
    scanf("%s", input);
    parse();
    return 0;
}
