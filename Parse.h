//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_PARSE_H
#define ZANKA_PARSE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Token_def.h"
#include "AST.h"


class Parser {
private:
    const std::vector<Token> token_list;
    Token token_now;
    int now_counter = 0;

    void token_check_next(Token_kind k);
    void token_check_now(Token_kind k);
    void read_Program();

    DECL_BLOCK_AST* read_Decl_block();

//    FUNC_DECL_AST *read_var_Decl(); //将来変数せんげんが追加されたらこれは変わる

    FUNC_DECL_AST *read_Func_decl();
    void read_Args(FUNC_DECL_AST* f);

    RET_STMT_AST *read_Ret_stmt();

    EXPR_AST *read_Expr();

    void next_token();

public:
    explicit Parser(std::vector<Token> t);
    ~Parser();


    void parse();

    void test_lex();

    void test_parse();

    PROGRAM_AST* program = new PROGRAM_AST();
};


#endif //ZANKA_PARSE_H
