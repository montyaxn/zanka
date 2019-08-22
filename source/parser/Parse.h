//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_PARSE_H
#define ZANKA_PARSE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../Token_def.h"
#include "../ast/AST.h"


class Parser {
private:
    const std::vector<Token> token_list;

    //トークン読み込み関係
    Token token_now;
    int now_counter = 0;
    void next_token();
    void token_check_next(Token_kind k);
    void token_check_now(Token_kind k);


    //LL文法解析
    void read_Program();
    std::unique_ptr<DECL_BLOCK_AST> read_Decl_block();
    std::unique_ptr<FUNC_DECL_AST> read_Func_decl();
    void read_Args(std::unique_ptr<FUNC_DECL_AST>& f);
    std::unique_ptr<RET_STMT_AST> read_Ret_stmt();
    std::unique_ptr<EXPR_AST> read_Expr();
    std::unique_ptr<EXPR_DASH_AST> read_Expr_Dash();
    std::unique_ptr<EXPR_T_AST> read_Expr_T();
    std::unique_ptr<EXPR_T_DASH_AST> read_Expr_T_DASH();
    std::unique_ptr<EXPR_F_AST> read_Expr_F();



public:
    explicit Parser(std::vector<Token> t);

    void parse();

    void test_lex();

    std::unique_ptr<PROGRAM_AST> program = nullptr;
};


#endif //ZANKA_PARSE_H
