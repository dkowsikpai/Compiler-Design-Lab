%{
#include "y.tab.h"
%}

%%

char|float|int return KEYWORD;
[a-zA-Z_][a-zA-Z0-9]* return ID;
\(\) return EMPTY_PARA;
. return yytext[0];
\n return;

%%

int yywrap() {
    return 1;
}