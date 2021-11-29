%{
    #include <stdio.h>
    int flag=1;    
%}

%token KEYWORD
%token STRUCT
%token ASSIGN
%token ID
%token NUM

%%

StructExpression:S {
    if (flag) 
        printf("Valid\n");
    return 1;
};

S: STRUCT' 'ID'{'BODY'}';

BODY: KEYWORD' 'ID';'|KEYWORD' 'ID ASSIGN NUM';'|S';';

%%

int main() {
    printf("Enter the expression: ");
    yyparse();
    return 1;
}

int yyerror() {
    flag = 0;
    printf("Error\n");
    return 0;
}