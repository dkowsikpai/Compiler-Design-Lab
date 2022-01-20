%{
#include "y.tab.h"
%}

%%

class return CLS;
public|private|protected return ACCESS;
char|float|int|double|void return DTYPE;
[a-zA-Z_][a-zA-Z0-9]* return ID;
\(\) return EMPTY_PARA;
. return yytext[0];
\n return;

%%

int yywrap() {
    return 1;
}