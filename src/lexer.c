#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

struct Lexer {
    const char *input;
    int pos;
};

Lexer *lexer_create(const char *input)
{
    Lexer *lexer = malloc(sizeof(Lexer));
    
    lexer->input = input;
    lexer->pos = 0;

    return lexer;
}

Lexer *lexer_destroy(Lexer *lexer)
{
    free(lexer);
    lexer = NULL;
}

// 工具函数
static char peek(Lexer *lexer)
{
    return lexer->input[lexer->pos];
}

static char advance(Lexer *lexer)
{
    return lexer->input[lexer->pos++];
}

static void skip_whitespace(Lexer *lexer)
{
    while (isspace((unsigned char)peek(lexer)))
        advance(lexer);
}

static int read_number(Lexer *lexer, Token *token)
{
    double val = 0;

    // 必须以数字开头
    if (!isdigit((unsigned char)peek(lexer))) {
        token->type = TOKEN_ERROR;
        snprintf(token->error, ERROR_MSG_BUFF_SIZE, "invalid number");
        return 0;
    }
    
    // 整数部分
    while (isdigit((unsigned char)peek(lexer)))
        val = val * 10 + (advance(lexer) - '0');

    // 小数部分
    if (peek(lexer) == '.') {
        advance(lexer);
        double base = 0.1;

        while (isdigit((unsigned char)peek(lexer))) {
            val += (advance(lexer) - '0') * base;
            base *= 0.1;
        }
    }

    token->type = TOKEN_NUMBER;
    token->value = val;
    return 1;
}

int next_token(Lexer *lexer, Token *token)
{
    skip_whitespace(lexer);

    char c = peek(lexer);

    if (c == '\0') {
        token->type = TOKEN_EOF;
        return 1;
    }
    if (isdigit((unsigned char)c)) {
        return read_number(lexer, token);
    }
    if (c == '+') {
        advance(lexer);
        token->type = TOKEN_PLUS;
        return 1;
    }
    if (c == '-') {
        advance(lexer);
        token->type = TOKEN_MINUS;
        return 1;
    }

    advance(lexer);
    token->type = TOKEN_ERROR;
    snprintf(token->error, ERROR_MSG_BUFF_SIZE, "unknown char: %c", c);
    return 0;
}
