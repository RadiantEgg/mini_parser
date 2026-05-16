#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "token.h"

// 工具函数
static AST *ast_create(void)
{
    AST *node = malloc(sizeof(AST));
    node->left = NULL;
    node->right = NULL;
    return node;
}

static AST *factor(Parser *parser)
{
    if (parser->cur.type == TOKEN_NUMBER)
    {
        AST *node = ast_create();
        node->type = AST_NUMBER;
        node->value = parser->cur.value;
        advance(parser);
        return node;
    }
    else if (parser->cur.type == TOKEN_LPAREN)
    {
        advance(parser);
        AST *subtree = expr(parser);
        if (parser->cur.type == TOKEN_RPAREN) {
            advance(parser);
            return subtree;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}


static AST *term(Parser *parser)
{
    AST *left = factor(parser);
    while (parser->cur.type == TOKEN_MUL || parser->cur.type == TOKEN_DIV) {
        AST *node = ast_create();
        node->type = (parser->cur.type == TOKEN_MUL) ? AST_MUL : AST_DIV;
        node->left = left;
        advance(parser);
        node->right = factor(parser);
        left = node;
    }
    return left;
}

static AST *expr(Parser *parser)
{
    AST *left = term(parser);
    while (parser->cur.type == TOKEN_PLUS || parser->cur.type == TOKEN_MINUS) {
        AST *node = ast_create();
        node->type = (parser->cur.type == TOKEN_PLUS) ? AST_ADD : AST_SUB;
        advance(parser);
        node->left = left;
        node->right = term(parser);
        left = node;
    }
    return left;
}


static void advance(Parser *parser)
{
    next_token(parser->lexer, &parser->cur);
}

AST *parse_expression(Lexer *lexer)
{
    AST *ast = ast_create();
    Parser parser;
    parser.lexer = lexer;
    advance(&parser);
    ast = expr(&parser);
    return ast;
}



double ast_eval(AST *node)
{
    switch(node->type) {
        case AST_NUMBER:
            return node->value;
        case AST_ADD:
            return ast_eval(node->left) + ast_eval(node->right);
        case AST_SUB:
            return ast_eval(node->left) - ast_eval(node->right);
        case AST_MUL:
            return ast_eval(node->left) * ast_eval(node->right);
        case AST_DIV:
            return ast_eval(node->left) / ast_eval(node->right);
        default:
            return 0;           
    }
    return 0;
}

