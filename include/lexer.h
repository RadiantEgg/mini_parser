#ifndef LEXER_H
#define LEXER_H

#include "token.h"

/* lexer 是一个字符流状态记录器，记录字符流 char *input 和当前位置 */

typedef struct Lexer Lexer;

/* 记录器 */
Lexer *lexer_create(const char *input);
void lexer_destroy(Lexer *lexer);

/* 核心==获取下一个token */
int next_token(Lexer *lexer, Token *token);

#endif