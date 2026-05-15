#ifndef TOKEN_H
#define TOKEN_H

#define ERROR_MSG_BUF_SIZE 64

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char error[ERROR_MSG_BUF_SIZE];
} Token;

void print_token(const Token *token);

#endif