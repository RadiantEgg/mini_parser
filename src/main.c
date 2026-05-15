#include <stdio.h>
#include "lexer.h"
#include "token.h"

int main()
{
    const char *input = "12 + 34 - 5";

    Lexer *lexer = lexer_create(input);

    Token token;

    printf("Input: %s\n\n", input);
    while (1) {
        int ok = next_token(lexer, &token);

        print_token(&token);
        if (token.type == TOKEN_EOF)
            break;
        if (token.type == TOKEN_ERROR) {
            printf("LEXER ERROR\n");
            break;
        }
    }
    lexer_destroy(lexer);
    return 0;
}