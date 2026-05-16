#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"

typedef enum {
    AST_NUMBER,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV
} ASTType;

typedef struct AST {
    ASTType type;
    double value;

    struct AST *left;
    struct AST *right;
} AST;

typedef struct {
    Lexer *lexer;
    Token cur;
} Parser;

AST *parse_expression(Lexer *lexer);
static AST *factor(Parser *parser);
static AST *term(Parser *parser);
static AST *expr(Parser *parser);
static void advance(Parser *parser);


void ast_free(AST *node);

double ast_eval(AST *node);


#endif