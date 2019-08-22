//
// Created by montyaxn on 19/06/21.
//

#include "Parse.h"

Parser::Parser(std::vector<Token> t) : token_list(std::move(t)) {
    next_token();
}


void Parser::parse() {
    read_Program();
}

//
// LL(1) Syntax analysis
//

void Parser::read_Program() {
    program = std::make_unique<PROGRAM_AST>(read_Decl_block());
}

std::unique_ptr<FUNC_DECL_AST> Parser::read_Func_decl() {
    auto tmp = std::make_unique<FUNC_DECL_AST>();
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
                std::cout << now_counter << std::endl;
                next_token();
                break;
        }
    }
    end:
    next_token();

    return tmp;
}

void Parser::read_Args(std::unique_ptr<FUNC_DECL_AST> &f) {
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

std::unique_ptr<DECL_BLOCK_AST> Parser::read_Decl_block() {
    auto tmp = std::make_unique<DECL_BLOCK_AST>();
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

std::unique_ptr<RET_STMT_AST> Parser::read_Ret_stmt() {
    auto tmp = std::make_unique<RET_STMT_AST>();
    tmp->make_expr(read_Expr());
    token_check_now(Token_kind::Semi_colon);
    next_token();
    return tmp;
}

std::unique_ptr<EXPR_AST> Parser::read_Expr() {
    auto tmp_T = read_Expr_T();
    if (token_now.kind == Token_kind::Plus or token_now.kind == Token_kind::Minus) {
        auto tmp_Dash = read_Expr_Dash();
        return std::make_unique<EXPR_AST>(std::move(tmp_T), std::move(tmp_Dash)); //More + or -
    }
    return std::make_unique<EXPR_AST>(std::move(tmp_T)); //No more + or -
}

std::unique_ptr<EXPR_T_AST> Parser::read_Expr_T() {
    auto tmp_F = read_Expr_F();
    if (token_now.kind == Token_kind::Mult or token_now.kind == Token_kind::Div) {
        auto tmp_Dash = read_Expr_T_DASH();
        return std::make_unique<EXPR_T_AST>(std::move(tmp_F), std::move(tmp_Dash)); //More * or /
    }
    return std::make_unique<EXPR_T_AST>(std::move(tmp_F)); //No more * or /
}

std::unique_ptr<EXPR_DASH_AST> Parser::read_Expr_Dash() {
    Ope ope;
    if (token_now.kind == Token_kind::Plus) {
        ope = Plus;
    } else {
        ope = Minus;
    }
    next_token();
    auto tmp_T = read_Expr_T();
    if (token_now.kind == Token_kind::Plus or token_now.kind == Token_kind::Minus) {
        auto tmp_Dash = read_Expr_Dash(); //More * or /
        return std::make_unique<EXPR_DASH_AST>(ope, std::move(tmp_T), std::move(tmp_Dash));
    }
    return std::make_unique<EXPR_DASH_AST>(ope, std::move(tmp_T));
}

std::unique_ptr<EXPR_T_DASH_AST> Parser::read_Expr_T_DASH() {
    Ope ope;
    if (token_now.kind == Token_kind::Mult) {
        ope = Mult;
    } else {
        ope = Div;
    }
    next_token();
    auto tmp_F = read_Expr_F();
    if (token_now.kind == Token_kind::Mult or token_now.kind == Token_kind::Div) {
        auto tmp_Dash = read_Expr_T_DASH(); //More * or /
        return std::make_unique<EXPR_T_DASH_AST>(ope, std::move(tmp_Dash), std::move(tmp_F));
    }
    return std::make_unique<EXPR_T_DASH_AST>(ope, std::move(tmp_F));
}

std::unique_ptr<EXPR_F_AST> Parser::read_Expr_F() {
    if (token_now.kind == Token_kind::L_paren) {
        next_token();
        auto expr = read_Expr();
        token_check_now(Token_kind::R_paren);
        next_token();
        return std::make_unique<EXPR_F_AST>(std::move(expr));
    } else if (token_now.kind == Token_kind::Integer_val) {
        auto val = std::make_unique<I32_EXPR_AST>(token_now.val);
        next_token();
        return std::make_unique<EXPR_F_AST>(std::move(val));
    }
//      else if (token_now.kind==Token_kind::Ident) {
//        return std::make_unique<EXPR_F_AST>();
//    }
    else {
        std::cout << "error" << std::endl;
        std::cout << now_counter << std::endl;
        return std::make_unique<EXPR_F_AST>(std::make_unique<I32_EXPR_AST>(0));
    }
}

//
// Token analysis
//

void Parser::next_token() {
    if (token_now.kind == Token_kind::End)
        return;
    token_now = token_list[now_counter];
    now_counter++;
}

void Parser::token_check_now(Token_kind k) {
    if (k != token_now.kind) {
        std::cout << "Syntax error! " << std::endl;
        std::cout << now_counter << std::endl;
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
