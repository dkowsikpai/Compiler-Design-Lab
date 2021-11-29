/** 
 * Author: Kowsik Nandagopan D
 * CSE S7 Roll No 31
 * Program: Design and implement a lexical analyzer for given language using C and the lexical
 * analyzer should ignore redundant spaces, tabs and new lines.
*/

// Import Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int isKeyword (char key[]) {
    /**
     *  Function to test whether it is a keyword or not. 
     * If it is a key word it will return 1 else 0 
    */
   // Predefined keyword list
    char keywords[32][10] = {
        "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };

    // Linear search of keywords
    for (int i=0; i < 32; i++) {
        if (strcmp(keywords[i], key) == 0) {
            return 1;
        }
    }
    return 0;
}


int isOperator (char op) {
    /**
     *  Function to test whether it is a operator or not. 
     * If it is a key word it will return 1 else 0 
    */
    char operators[] = "/*-+=%^";
    for (int i=0; i < 7; i++) {
        if (operators[i] == op) return 1;
    }
    return 0;
}

void main() {

    char ch[20];
    int i = 0;

    // Input Output files
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    // If file creation/reading failed
    if (in == NULL || out == NULL) {
        printf("Error in opening file.");
        exit(0);
    }

    // Analysis
    while ((ch[i] = fgetc(in)) != EOF) {
        if (isOperator(ch[i]) == 1) {
            // If character is a operator
            printf("%c is OPERATOR\n", ch[i]);
            fprintf(out, "%c is OPERATOR\n", ch[i]);
            i = 0;
            continue;
        } else if (!isalnum(ch[i])) {
            // If character is a not alpha-num.
            // Means its either space, delimiter, comma we have to test the curremt buffer
            ch[i] = '\0';
            if (isKeyword(ch) == 1) {
                // If keryword
                printf("%s is KEYWORD\n", ch);
                fprintf(out, "%s is KEYWORD\n", ch);
            } else if (strlen(ch) > 0) {
                // If Identifier
                printf("%s is IDENTIFIER\n", ch);
                fprintf(out, "%s is IDENTIFIER\n", ch);
            }
            i = 0;
            continue;
        } else {
            i++;
        }
    }
    
    printf("\n");

    // Close file pointer
    fclose(in);
    fclose(out);
}