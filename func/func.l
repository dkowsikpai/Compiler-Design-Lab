%{
	#include <stdio.h>
	#include "y.tab.h"
%}

%%

int|float|char return KEYWORD;
[a-zA-Z_0-9]* return ID;

. return yytext[0];

%%

int yywrap() {
	return 1;
}
