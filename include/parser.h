#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "token.h"

/* 定义树节点类型 */
typedef enum {
    AST_NUMBER,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV
} ASTType;

/* 定义数节点，包括节点类型、值、左右子节点 */
typedef struct AST {
    ASTType type;
    double value;

    struct AST *left;
    struct AST *right;
} AST;

/* 有限状态机，包含字符流记录器和当前token */
typedef struct {
    Lexer *lexer;
    Token cur;
} Parser;

/* 解析文本入口：把字符流转化为的token流进一步转化为树的语法结构 */
AST *parse_expression(Lexer *lexer);


static AST *factor(Parser *parser);
static AST *term(Parser *parser);
static AST *expr(Parser *parser);
static void advance(Parser *parser);

/* 解析树并按照语法结构运算 */
double ast_eval(AST *node);

void ast_free(AST *node);



#endif