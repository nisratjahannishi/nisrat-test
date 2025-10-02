#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void lexicalAnalyzer(FILE *in, FILE *out)
{
    int c,i=0,isF=0;
    char num[20];
    printf("\nTokens (Numbers) found in the input with their attribute values are:\n");
    while((c=fgetc(in))!=EOF)
    {
        if(c==' ') continue;                     // space বাদ
        if(isdigit(c)||c=='.')                   // সংখ্যা collect
        {
            if(c=='.') isF=1;
            num[i++]=c;
        }
        else
        {
            if(i)
            {
                num[i]='\0';                  // সংখ্যা শেষ হলে token print
                if(isF) printf("<number, floating-point value %g>\n", atof(num));
                else   printf("<number, integer value %d>\n", atoi(num));
                i=0;
                isF=0;
            }
            fputc(c,out);                        // বাকি character output.c তে লিখে
        }
    }
}

int main()
{
    FILE *in=fopen("input.c","r"), *out=fopen("output.c","w");
    if(!in||!out)
    {
        printf("Error opening files.\n");
        return 1;
    }

    printf("Lexical analysis complete. Check 'output.c' for the result.\n");
    lexicalAnalyzer(in,out);

    fclose(in);
    fclose(out);
    return 0;
}

