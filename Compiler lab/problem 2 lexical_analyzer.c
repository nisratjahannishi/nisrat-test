#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 100

// Function to eliminate whitespace and collect numbers as token
void lexicalAnalyzer(FILE *inputFile, FILE *outputFile)
{
    char line[MAX_LINE_LENGTH];
    int intNum;        // To collect integer numbers
    float floatNum;    // To collect floating point numbers

    printf("\nTokens (Numbers) found in the input with their attribute values are: \n");

    // Read input file line by line
    while(fgets(line, sizeof(line), inputFile) != NULL)
    {
        int len = strlen(line);

        // If the last character is a newline, exclude it from the length
        if(line[len - 1] == '\n')
            len--;

        int i, j;
        char resLine[MAX_LINE_LENGTH];
        for(i = 0, j = 0; i < len; i++)
        {
            if(line[i] == ' ')
                continue;

            else if(line[i] == '"')
            {
                resLine[j++] = line[i++];
                while(line[i] != '"')
                    resLine[j++] = line[i++];

                resLine[j++] = line[i];
            }

            else if((line[i] >= '0' && line[i] <= '9'))
            {
                int k = 0;
                char strNum[20];
                bool isFloatNum = false;
                while((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
                {
                    if(line[i] == '.')
                        isFloatNum = true;

                    resLine[j++] = line[i];
                    strNum[k++] = line[i++];
                }

                i--;
                strNum[k] = '\0';

                if(isFloatNum)
                {
                    sscanf(strNum, "%f", &floatNum);
                    printf("<number, floating-point value %g>\n", floatNum);
                }

                else
                {
                    sscanf(strNum, "%d", &intNum);
                    printf("<number, integer value %d>\n", intNum);
                }
            }

            else
                resLine[j++] = line[i];
        }

        if(j > 0)
        {
            resLine[j++] = '\n';
            resLine[j] = '\0';

            // Writing each line to the output file
            fprintf(outputFile, "%s", resLine);
        }
    }
}

int main()
{
    FILE *inputFile = fopen("input.c", "r");
    FILE *outputFile = fopen("output.c", "w");

    if(inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    printf("Lexical analysis complete. Check 'output.c' for the result.\n");

    // Call the lexical analyzer function
    lexicalAnalyzer(inputFile, outputFile);

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
