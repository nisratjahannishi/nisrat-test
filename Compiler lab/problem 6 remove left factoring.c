#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 100

char input[MAX_LEN];  // To store rule

void remove_left_factoring()
{
    char LHS;    // To store left-hand side
    char RHS[MAX_LEN]; // right-hand side
    int bar = 0;

    // Separate LHS and RHS
    for(int i = 0; i < strlen(input); i++)
    {
        if(input[i] >= 'A' && input[i] <= 'Z')
        {
            LHS = input[i++];

            int j = 0;
            while(i < strlen(input))
            {
                if(input[i] == ' ' || input[i] == '-' || input[i] == '>')
                {
                    i++;
                    continue;
                }

                RHS[j++] = input[i++];
            }

            RHS[j] = '\0';
        }
    }

    char parts_prod[MAX_LEN][MAX_LEN];
    int len = strlen(RHS), pp_len = 0;

    // Separate production into 2d array by |
    for(int i = 0; i < len; i++)
    {
        int j = 0;
        while(i < len && RHS[i] != '|')
            parts_prod[pp_len][j++] = RHS[i++];

        parts_prod[pp_len++][j] = '\0';
    }

    printf("\nAfter Removing left factoring:\n");

    // Loop until no match
    while(1)
    {
        int max_common_prefix_idx = -1;
        for(int i = 1; i < pp_len; i++)
        {
            if(parts_prod[i][0] == parts_prod[0][0])
                max_common_prefix_idx = i;
            else
                break;
        }

        // Print next rule LHS
        printf("%c", LHS);
        for(int i = 1; i <= bar; i++)
            printf("'");
        printf(" -> ");
        bar++;

        if(max_common_prefix_idx == -1)
        {
            for(int i = 0; i < pp_len; i++)
            {
                if(i > 0)
                    printf(" | ");

                for(int j = 0; j < strlen(parts_prod[i]); j++)
                    printf("%c", parts_prod[i][j]);
            }

            printf("\n");
            break;
        }

        // Print next rule RHS
        int max_common_prefix_len = 0;
        for(int j = 0; ; j++)
        {
            char temp;

            if(parts_prod[0][j] != '\0')
                temp = parts_prod[0][j];
            else
                break;

            bool all_matched = true;
            for(int i = 0; i <= max_common_prefix_idx; i++)
            {
                if(parts_prod[i][j] == '\0' || parts_prod[i][j] != temp)
                {
                    all_matched = false;
                    break;
                }
            }

            if(all_matched)
            {
                printf("%c", temp);
                max_common_prefix_len = j + 1;
            }
        }

        printf("%c", LHS);
        for(int i = 1; i <= bar; i++)
            printf("'");

        for(int i = max_common_prefix_idx + 1; i < pp_len; i++)
            printf(" | %s", parts_prod[i]);

        printf("\n");

        // Update parts_prod array
        pp_len = 0;
        bool flag = false;
        for(int i = 0; i <= max_common_prefix_idx; i++)
        {
            int k = 0;
            for(int j = max_common_prefix_len; j < strlen(parts_prod[i]); j++, k++)
                parts_prod[pp_len][k] = parts_prod[i][j];

            if(k > 0)
                parts_prod[pp_len++][k] = '\0';
            else
                flag = true;
        }

        if(flag)
        {
            parts_prod[pp_len][0] = 'e';    // add epsilon
            parts_prod[pp_len++][1] = '\0';
        }
    }
}

int main()
{
    printf("Enter the production: ");
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline
    remove_left_factoring();
    return 0;
}
