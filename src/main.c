#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "token.h"

int main()
{
    const char *input = "  1.5  *( 2 / 3 *(1 + 2) )";

    Lexer *lexer = lexer_create(input);

    Token token;

    printf("Input: %s\n\n", input);
    /*while (1) {
        int ok = next_token(lexer, &token);

        print_token(&token);

        if (token.type == TOKEN_EOF || token.type == TOKEN_ERROR)
            break;
    }*/

    AST *node = parse_expression(lexer);
    double result = ast_eval(node);
    printf("Result: %.2f\n", result);
    lexer_destroy(lexer);
    return 0;
}