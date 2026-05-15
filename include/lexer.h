#ifndef LEXER_H
#define LEXER_H

#include "token.h"

#define ERROR_MSG_BUFF_SIZE 64

// opaque struct
typedef struct Lexer Lexer;

// 创建词法解析器
Lexer *lexer_create(const char *input);
// 销毁词法解析器
Lexer *lexer_destroy(Lexer *lexer);

// 获取下一个token
int next_token(Lexer *lexer, Token *token);

#endif