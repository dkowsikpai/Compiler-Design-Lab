%{
	#include <stdio.h>
	int flag=1;
%}

%token KEYWORD
%token ID

%%

FunctionDef: E {
	if(flag)
		printf("Valid\n");
	return 1;
};

E: KEYWORD' 'ID'('PARA')'';';

PARA: KEYWORD' 'ID|KEYWORD' 'ID','PARA;

%%

int main() {
	printf("Enter the expression: ");
	yyparse();
	return 1;
}

int yyerror() {
	flag = 0;
	printf("Error");
	return 0;
}
