#include <stdio.h>
#include "token.h"

void print_token(const Token *token)
{
    switch(token->type) {
        case TOKEN_NUMBER:
            printf("NUMBER: %.2f\n", token->value);
            break;
        case TOKEN_PLUS:
            printf("+\n");
            break;
        case TOKEN_MINUS:
            printf("-\n");
            break;
        case TOKEN_ERROR:
            printf("LEXER ERROR\n");
            break;
        case TOKEN_EOF:
            printf("EOF\n");
            break;
    }
}