%{
#include<stdio.h>
#include "y.tab.h"
%}

%%
for return FOR;
[0-9]+ return NUM;
\+\+|\-\- return UPDATE;
\>|\<|\>\=|\<\= return LOGIC;
[a-zA-Z0-9]+ return TOKEN;



. return yytext[0];

%%

int yywrap(){
    return 1;
}
