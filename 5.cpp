// Write a Lex program to generate tokens as
// identifiers, keywords, newline, tabs,
// whitespaces and characters.

%{
#include <stdio.h>
%}
%%
int|return|if|else|while { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }
\n { printf("Newline\n"); }
\t { printf("Tab\n"); }
[ ]+ { printf("Whitespace\n"); }
{ printf("Character: %s\n", yytext); }
%%
int main() {
yylex();
return 0;
}
