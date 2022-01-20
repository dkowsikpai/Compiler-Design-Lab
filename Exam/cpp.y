%{
#include <stdio.h>    
int flag = 1;
%}

%token CLS ACCESS DTYPE ID EMPTY_PARA

%%

ClassDef: CLS' 'ID'{'BODY'}'';';

BODY: ACCESS':'MEMBERS|ACCESS':'MEMBERS BODY;

MEMBERS: DTYPE' 'ID';'
        |DTYPE' 'ID';'FunctionDef
        |DTYPE' 'ID';'FunctionDef MEMBERS
        |DTYPE' 'ID';'MEMBERS;

FunctionDef: DTYPE' 'ID EMPTY_PARA'{'FunBody'}'|DTYPE' 'ID'('PARA')''{'FunBody'}';

PARA: DTYPE' 'ID|DTYPE' 'ID','PARA;

FunBody: DTYPE' 'ID';'
        |ID'='Expr;

Expr: ID'+'ID';'
    |ID'-'ID';'
    |ID'*'ID';'
    |ID'/'ID';';

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
