#include <stdio.h>
#include "lexer.h"
#include "token.h"

int main()
{
    const char *input = "   a1.2 + 0.34 -";

    Lexer *lexer = lexer_create(input);

    Token token;

    printf("Input: %s\n\n", input);
    while (1) {
        int ok = next_token(lexer, &token);

        print_token(&token);

        if (token.type == TOKEN_EOF || token.type == TOKEN_ERROR)
            break;
    }
    lexer_destroy(lexer);
    return 0;
}