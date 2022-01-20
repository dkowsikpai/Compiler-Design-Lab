%{
#include <stdio.h>    
int flag = 1;
%}

%token KEYWORD ID EMPTY_PARA

%%

FunctionDef: KEYWORD' 'ID EMPTY_PARA|KEYWORD' 'ID'('PARA')';

PARA: KEYWORD' 'ID|KEYWORD' 'ID','PARA;

%%

int yyerror() {
    flag = 0;
    printf("Invalid expression\n");
    return 0;
}

int main() {
    printf("Enter the expression:");
    yyparse();
    if (flag)
        printf("Valid expression\n");
    return 1;
}
