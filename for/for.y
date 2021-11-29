%{
#include <stdio.h>
int flag = 1;
%}

%token TOKEN
%token NUM
%token FOR
%token UPDATE
%token LOGIC

%%

ForGrammar:F {
    if (flag){
        printf("Valid");
        return 1;
    }
    return 0;
};

F:FOR'('E1';'E2';'E3')'BLOCK;
E1:TOKEN'='E|NUM|TOKEN;

E2:E LOGIC E;

E3:E UPDATE|TOKEN'='E;

E:E'+'E|E'-'E|E'*'E|E'/'E|'('E')'|NUM|TOKEN;

BLOCK:'{'BODY'}';
BODY: F|E1|;

%%

int main (){
    printf("Enter for statement: ");
    yyparse();
    return 1;
}
 
int yyerror(){
    flag = 0;
    printf("Error");
    return 0;
}
