#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    FILE *in=fopen("input.c","r"), *out=fopen("output.c","w");
    if(!in||!out)
    {
        printf("Error opening files.\n");
        return 1;
    }

    printf("Lexical analysis complete. Check 'output.c' for the result.\n\n");
    printf("Numbers found in the input:\n");

    int c;
    char num[20];
    int i=0;
    int isFloat=0;
    while((c=fgetc(in))!=EOF)
    {
        if(c==' ') continue;
        if(isdigit(c)||c=='.')
        {
            if(c=='.') isFloat=1;
            num[i++]=c;
        }
        else
        {
            if(i)
            {
                num[i]='\0';
                printf(isFloat?"%g\n":"%d\n", isFloat?atof(num):atoi(num));
                i=0;
                isFloat=0;
            }
            fputc(c,out);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}

