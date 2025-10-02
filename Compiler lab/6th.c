#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

// Remove spaces
void remove_spaces(char *s) {
    int j = 0;
    for(int i = 0; s[i]; i++)
        if(!isspace(s[i])) s[j++] = s[i];
    s[j] = '\0';
}

// Recursive left factoring
void left_factoring(char lhs, char rhs[], int level) {
    char *parts[20];
    int n = 0;
    char temp[MAX];
    strcpy(temp, rhs);

    // Split by '|'
    char *tok = strtok(temp, "|");
    while(tok) { parts[n++] = tok; tok = strtok(NULL, "|"); }

    // Find common prefix
    int prefix = 0;
    while(1) {
        char c = parts[0][prefix];
        if(c == '\0') break;
        int i;
        for(i = 1; i < n; i++) if(parts[i][prefix] != c) break;
        if(i < n) break;
        prefix++;
    }

    if(prefix == 0) { // No common prefix
        printf("%c -> ", lhs);
        for(int i=0;i<n;i++){ printf("%s", parts[i]); if(i<n-1) printf(" | "); }
        printf("\n");
        return;
    }

    // New non-terminal name
    char new_lhs[5];
    sprintf(new_lhs, "%c", lhs);
    for(int i=0;i<level;i++) strcat(new_lhs,"'");

    printf("%c -> %.*s%s\n", lhs, prefix, parts[0], new_lhs);

    // Prepare new RHS
    char new_rhs[MAX] = "";
    for(int i=0;i<n;i++){
        char *s = parts[i]+prefix;
        if(strlen(s)==0) strcat(new_rhs,"e");
        else strcat(new_rhs,s);
        if(i<n-1) strcat(new_rhs,"|");
    }

    // Recursive call
    left_factoring(new_lhs[0], new_rhs, level+1);
}

int main() {
    char input[MAX];
    printf("Enter the production: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0;

    char lhs = input[0];
    char *rhs = strchr(input, '>') + 1;
    remove_spaces(rhs);

    left_factoring(lhs, rhs, 1);
    return 0;
}
