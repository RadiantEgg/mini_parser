#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer.h"

struct Lexer {
    const char *input;
    int pos;
};

Lexer *lexer_create(const char *input)  /* 创建记录器 */
{
    Lexer *lexer = malloc(sizeof(Lexer));
    
    lexer->input = input;
    lexer->pos = 0;

    return lexer;
}

void lexer_destroy(Lexer *lexer)
{
    free(lexer);
}

// 工具函数
static char peek(Lexer *lexer)  /* 查看字符流当前字符 */
{
    if (lexer->input[lexer->pos] == '\0') {
        return '\0';
    } else {
        return lexer->input[lexer->pos];
    }
}

static char advance(Lexer *lexer)   /* 消耗字符并向前移动一个字符 */
{
    return lexer->input[lexer->pos++];
}

static void skip_whitespace(Lexer *lexer)   /* 跳过空白字符 */
{
    while (isspace((unsigned char)peek(lexer)))
        advance(lexer);
}

static int read_number(Lexer *lexer, Token *token)  /* 读取数字 */
{
    double val = 0;

    // 必须以数字开头
    if (!isdigit((unsigned char)peek(lexer))) {
        token->type = TOKEN_ERROR;
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

/* 在字符流中回去下一个非空token并记录在token指针中 */
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
    if (c == '*') {
        advance(lexer);
        token->type = TOKEN_MUL;
        return 1;
    }
    if (c == '/') {
        advance(lexer);
        token->type = TOKEN_DIV;
        return 1;
    }
    if (c == '(') {
        advance(lexer);
        token->type = TOKEN_LPAREN;
        return 1;
    }
    if (c == ')') {
        advance(lexer);
        token->type = TOKEN_RPAREN;
        return 1;
    }

    advance(lexer);
    token->type = TOKEN_ERROR;
    token->value = c;
    return 0;
}
