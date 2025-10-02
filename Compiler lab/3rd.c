#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Check এটা function কিনা (পরের দিকে '(' থাকলে function)
int isFunction(char *s, int i, int n)
{
    while(i<n) if(s[i++]=='(') return 1;
    return 0;
}

// Variable detect করা
void findVars(char *s, int i, int n)
{
    while(i<n && s[i]!=';')
    {
        if(isalpha(s[i])||s[i]=='_')
        {
            char v[MAX];
            int j=0;
            while(i<n && (isalnum(s[i])||s[i]=='_')) v[j++]=s[i++];
            v[j]='\0';
            if(!isFunction(s,i,n)) printf("%s\n",v);
        }
        i++;
    }
}

void lexicalAnalyzer(FILE *in)
{
    char line[MAX];
    printf("Variables found in the input are:\n");
    while(fgets(line,sizeof(line),in))
    {
        int n=strlen(line);
        if(line[n-1]=='\n') n--;
        for(int i=0; i<n; i++)
        {
            if(!strncmp(&line[i],"int ",4))
            {
                findVars(line,i+4,n);
                i+=3;
            }
            if(!strncmp(&line[i],"long ",5))
            {
                findVars(line,i+5,n);
                i+=4;
            }
            if(!strncmp(&line[i],"char ",5))
            {
                findVars(line,i+5,n);
                i+=4;
            }
            if(!strncmp(&line[i],"float ",6))
            {
                findVars(line,i+6,n);
                i+=5;
            }
            if(!strncmp(&line[i],"double ",7))
            {
                findVars(line,i+7,n);
                i+=6;
            }
        }
    }
}

int main()
{
    FILE *in=fopen("input1.c","r");
    if(!in)
    {
        printf("Error opening input file.\n");
        return 1;
    }
    lexicalAnalyzer(in);
    fclose(in);
}

