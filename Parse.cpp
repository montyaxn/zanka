//
// Created by montyaxn on 19/06/21.
//

#include "Parse.h"

Parser::Parser(std::vector<Token> t) : token_list(std::move(t)) {
    next_token();
}

Parser::~Parser() {
    delete (program);
}

void Parser::parse() {
    std::cout << "Parse start!" << std::endl;
    read_Program();
    std::cout << "Parse end" << std::endl;

}

void Parser::read_Program() {
    std::cout << "here1" << std::endl;
    program->decl_block = read_Decl_block();
}

FUNC_DECL_AST *Parser::read_Func_decl() {
    std::cout << "here2" << std::endl;
    auto tmp = new FUNC_DECL_AST();
    tmp->name = token_now.str;
    token_check_next(Token_kind::Colon);
    token_check_next(Token_kind::L_paren);
    next_token();
    read_Args(tmp);
    token_check_now(Token_kind::L_brace);
    next_token();

    while (true) {
        switch (token_now.kind) {
            case Token_kind::Return:
                next_token();
                tmp->add_stmt(read_Ret_stmt());
                break;
            case Token_kind::R_brace:
                goto end;
            default:
                std::cout << "error" << std::endl;
                next_token();
                break;
        }
    }
    end:
    next_token();

    return tmp;
}

void Parser::read_Args(FUNC_DECL_AST *f) {
    switch (token_now.kind) {
        default:
            next_token();
            std::cout << "error";
            break;
        case Token_kind::R_paren:
            next_token();
            break;
        case Token_kind::Ident:
            ARG arg;
            arg.name = token_now.str;
            token_check_next(Token_kind::Colon);
            token_check_next(Token_kind::Ident);
            arg.type = token_now.str;
            f->add_arg(arg);
            next_token();
            while (token_now.kind == Token_kind::Comma) {
                token_check_next(Token_kind::Ident);
                ARG arg1;
                arg1.name = token_now.str;
                token_check_next(Token_kind::Colon);
                token_check_next(Token_kind::Ident);
                arg1.type = token_now.str;
                f->add_arg(arg1);
                next_token();
            }
            token_check_now(Token_kind::R_paren);
            next_token();
            if (token_now.kind == Token_kind::Arrow) {
                token_check_next(Token_kind::Ident);
                f->make_ret_type(token_now.str);
                next_token();
            }
            break;
    }
}

DECL_BLOCK_AST *Parser::read_Decl_block() {
    std::cout << "here3" << std::endl;

    auto tmp = new DECL_BLOCK_AST();
    while (true) {
        switch (token_now.kind) {
            case Token_kind::Map:
                token_check_next(Token_kind::Ident);
                tmp->add_decl(read_Func_decl());
                break;
            default:
                goto end;
        }
    }
    end:
    return tmp;
}

RET_STMT_AST *Parser::read_Ret_stmt() {
    std::cout << "here 4" << std::endl;

    auto tmp = new RET_STMT_AST();
    tmp->expr = read_Expr();
    token_check_now(Token_kind::Semi_colon);
    next_token();
    return tmp;
}

EXPR_AST *Parser::read_Expr() {
    std::cout << "here5" << std::endl;

    auto tmp = new EXPR_AST();
    token_check_now(Token_kind::Integer_val);
    tmp->val = token_now.val;
    next_token();
    return tmp;
}

void Parser::next_token() {
    if (token_now.kind == Token_kind::End)
        return;
    token_now = token_list[now_counter];
    now_counter++;
}

void Parser::token_check_now(Token_kind k) {
    if (k != token_now.kind) {
        std::cout << "Syntax error! " << std::endl;
    }
}

void Parser::token_check_next(Token_kind k) {
    next_token();
    token_check_now(k);
}


void Parser::test_lex() {
    for (const Token &t : token_list) {
        std::cout << int(t.kind) << std::endl;
    }
}

void Parser::test_parse() {
    program->show();
}