#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

// List of C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int isKeyword(char *word)
{
    // Calculate number of keywords
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    // Check if the word matches any of the C language keywords
    for(int i = 0; i < num_keywords; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

void lexicalAnalyzer(FILE *inputFile)
{
    int serial_num = 1;
    char line[MAX_LINE_LENGTH];
    char buffer[MAX_LINE_LENGTH];  // Buffer to store potential keywords

    printf("Recognized keywords are:\n");

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
            else if(line[i] >= 'a' && line[i] <= 'z')
            {
                int idx = 0;
                while(i < len && line[i] >= 'a' && line[i] <= 'z')
                    buffer[idx++] = line[i++];

                buffer[idx] = '\0';

                if((line[i] == ' ' || line[i] == '(' || i == len) && isKeyword(buffer))
                {
                    printf("%d. %s\n", serial_num, buffer);
                    serial_num++;
                }
            }
        }
    }
}

int main()
{
    FILE *inputFile = fopen("input2.c", "r");

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
