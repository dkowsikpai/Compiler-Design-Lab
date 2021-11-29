%{
    #include <stdio.h>
    #include "y.tab.h"    
%}

%%

struct return STRUCT;
int|char|float return KEYWORD;
\= return ASSIGN;
[0-9]*(\.[0-9]*)? return NUM;
[a-zA-Z_0-9]* return ID;

. return yytext[0];

%%

int yywrap() {
    return 1;
}
