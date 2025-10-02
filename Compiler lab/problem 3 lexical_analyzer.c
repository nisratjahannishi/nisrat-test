#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 100

bool isFunction(char str[], int i, int len)
{
    for( ; i < len; i++)
    {
        if(str[i] == '(')
            return true;
    }

    return false;
}

void findVariables(char str[], int i, int len)
{
    for( ; i < len && str[i] != ';'; i++)
    {
        if(str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
        {
            int j = 0;
            char variable[MAX_LINE_LENGTH];
            while(str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9'))
                variable[j++] = str[i++];

            if(!isFunction(str, i, len))
            {
                variable[j] = '\0';
                printf("%s\n", variable);

                while(i < len)
                {
                    if(str[i] == ',')
                        break;

                    if(str[i] == ';')
                    {
                        i--;
                        break;
                    }

                    i++;
                }
            }

            else
                return;
        }
    }
}

void lexicalAnalyzer(FILE *inputFile)
{
    char line[MAX_LINE_LENGTH];

    printf("Variables found in the input are:\n");

    // Read input file line by line
    while(fgets(line, sizeof(line), inputFile) != NULL)
    {
        int len = strlen(line);

        // If the last character is a newline, exclude it from the length
        if(line[len - 1] == '\n')
            len--;

        for(int i = 0; i < len; i++)
        {
            if(line[i] == ' ')
                continue;
            else if(line[i] == '"')
            {
                i++;
                while(line[i] != '"')
                    i++;
            }
            else if(i + 3 < len && line[i] == 'i' && line[i+1] == 'n' && line[i+2] == 't' && line[i+3] == ' ')
                findVariables(line, i + 4, len), i = i + 3;
            else if(i + 4 < len && line[i] == 'l' && line[i+1] == 'o' && line[i+2] == 'n' && line[i+3] == 'g' && line[i+4] == ' ')
                findVariables(line, i + 5, len), i = i + 3;
            else if(i + 4 < len && line[i] == 'c' && line[i+1] == 'h' && line[i+2] == 'a' && line[i+3] == 'r' && line[i+4] == ' ')
                findVariables(line, i + 5, len), i = i + 3;
            else if(i + 5 < len && line[i] == 'f' && line[i+1] == 'l' && line[i+2] == 'o' && line[i+3] == 'a' && line[i+4] == 't' && line[i+5] == ' ')
                findVariables(line, i + 6, len), i = i + 4;
            else if(i + 6 < len && line[i] == 'd' && line[i+1] == 'o' && line[i+2] == 'u' && line[i+3] == 'b' && line[i+4] == 'l' && line[i+5] == 'e' && line[i+6] == ' ')
                findVariables(line, i + 6, len), i = i + 5;
        }
    }
}

int main()
{
    FILE *inputFile = fopen("input1.c", "r");

    if(inputFile == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    // Call the lexical analyzer function
    lexicalAnalyzer(inputFile);

    // Close the files
    fclose(inputFile);

    return 0;
}
