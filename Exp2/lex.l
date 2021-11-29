/** 
 * Author: Kowsik Nandagopan D
 * CSE S7 Roll No 31
 * Program: Implementation of Lexical Analyzer using Lex Tool
*/

%{
    int COMMENT = 0;
%}

identifier [a-zA-Z][a-zA-Z0-9]*

%%

#.* { printf("\n %s is Preprocessor Directive", yytext); }

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" {printf("\n %s is Keyword", yytext);}

"/*" {COMMENT = 1;} {printf("\n %s is Comment", yytext);}
"*/" {COMMENT = 0;} {printf("\n %s is Comment", yytext);}

\{ {if (!COMMENT) printf("\n %s Block Begins", yytext);}
\} {if (!COMMENT) printf("\n %s Block Ends", yytext);}

{identifier}(\[[0-9]*\])? {if (!COMMENT) printf("\n %s is Identifier", yytext);}

\".*\" {if (!COMMENT) printf("\n %s is String", yytext);}

[0-9]+ {if (!COMMENT) printf("\n %s is Number", yytext);}

= {if (!COMMENT) printf("\n %s is Assignment Operator", yytext);}
\<|\>|\<=|\>=|\==|\!= {if (!COMMENT) printf("\n %s is Relational Operator", yytext);}
\/|\*|\-|\+ {if (!COMMENT) printf("\n %s is Arithmetic Operator", yytext);}

\( {if (!COMMENT) printf("\n %s is Opening Bracket", yytext);}
\) {if (!COMMENT) printf("\n %s is Closing Bracket", yytext);}



%%

int main() {
    FILE *in = fopen("input.txt", "r");

    if (!in) {
        printf("Cannot open file!!!");
        exit(0);
    }

    yyin = in;
    yylex();

    printf("\n");
    return 0;
}

int yywrap(){
    return 1;
}
