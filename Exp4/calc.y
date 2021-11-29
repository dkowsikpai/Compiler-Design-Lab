%{
    #include <stdio.h>
    int flag = 1;
%}

%token NUMBER

%left '+''-'
%right '*''/''%'
%left '('')'

%%

ArithematicExpression:E {
    if (flag) printf("Result = %d\n", $$);
    else printf("Expression error");
    return 0;
};

E:E'+'E{$$=$1+$3;}
    |E'-'E{$$=$1-$3;}
    |E'*'E{$$=$1*$3;}
    |E'/'E{$$=$1/$3;}
    |E'%'E{$$=$1%$3;}
    |'('E')'{$$=$2;}
    |NUMBER{$$=$1;};

%%

int main() {
    printf("Enter Expression: ");
    yyparse();
    return 1;
}

int yyerror() {
    flag = 0;
    return 0;
}
