#include <stdio.h>
#include <string.h>

const char *keywords[] =
{
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","int",
    "long","register","return","short","signed","sizeof","static","struct",
    "switch","typedef","union","unsigned","void","volatile","while"
};

int isKeyword(char *w)
{
    for(int i=0; i<sizeof(keywords)/sizeof(keywords[0]); i++)
        if(strcmp(w,keywords[i])==0) return 1;
    return 0;
}

void lexicalAnalyzer(FILE *in)
{
    char line[100], buf[100];
    int serial=1;
    printf("Recognized keywords are:\n");

    while(fgets(line,sizeof(line),in))
    {
        int n=strlen(line);
        if(line[n-1]=='\n') n--;
        for(int i=0; i<n; i++)
        {
            if(line[i]==' ') continue;
            if(line[i]=='"')
            {
                while(line[i++]!='"');
                continue;
            }
            if(line[i]>='a' && line[i]<='z')
            {
                int j=0;
                while(i<n && line[i]>='a' && line[i]<='z') buf[j++]=line[i++];
                buf[j]='\0';
                if((line[i]==' '||line[i]=='('||i==n) && isKeyword(buf))
                    printf("%d. %s\n", serial++, buf);
            }
        }
    }
}

int main()
{
    FILE *in=fopen("input2.c","r");
    if(!in)
    {
        printf("Error opening input file.\n");
        return 1;
    }
    lexicalAnalyzer(in);
    fclose(in);
}

