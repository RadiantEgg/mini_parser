#ifndef TOKEN_H
#define TOKEN_H

/* 定义token类型：目前有数字、加减乘除、左右括号、错误以及字符流结束 */
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

/* 定义Token结构体，包含token类型以及对应值 */
typedef struct {
    TokenType type;
    double value;
} Token;

void print_token(const Token *token);   /* 打印测试 */

#endif