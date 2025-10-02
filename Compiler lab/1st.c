#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

void lexicalAnalyzer(FILE *in, FILE *out)
{
    char line[MAX];
    while (fgets(line, sizeof(line), in))
    {
        char res[MAX], num[20];
        int i=0, j=0, k;
        bool isFloat;

        while (line[i])
        {
            if (line[i]==' ')
            {
                i++;    // space বাদ
                continue;
            }
            if (line[i]=='"')                              // string 그대로
            {
                res[j++]=line[i++];
                while(line[i] && line[i]!='"') res[j++]=line[i++];
                res[j++]=line[i++];
            }
            else if (line[i]>='0' && line[i]<='9')         // number
            {
                k=0;
                isFloat=false;
                while((line[i]>='0'&&line[i]<='9')||line[i]=='.')
                {
                    if(line[i]=='.') isFloat=true;
                    num[k++]=line[i];
                    res[j++]=line[i++];
                }
                num[k]='\0';
                if(isFloat) printf("%g\n", atof(num));
                else printf("%d\n", atoi(num));
            }
            else res[j++]=line[i++];
        }
        res[j]='\0';
        fputs(res,out);
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

    printf("Lexical analysis complete. Check 'output.c' for the result.\n\n");
    printf("Numbers found in the input:\n");

    lexicalAnalyzer(in,out);

    fclose(in);
    fclose(out);
    return 0;
}

