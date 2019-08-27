//
// Created by montyaxn on 19/06/21.
//

#include "Parse.h"
#include <map>
#include <string>

static std::map<std::string, int> BiOpPrecedence;

Parser::Parser(std::vector<Token> t) : token_list(std::move(t)) {
    next_token();
    initialize_BiOpPrecedence();
}

void Parser::initialize_BiOpPrecedence() {
    BiOpPrecedence["<"] = 10;
    BiOpPrecedence[">"] = 10;
    BiOpPrecedence["=="] = 10;
    BiOpPrecedence["<="] = 10;
    BiOpPrecedence[">="] = 10;
    BiOpPrecedence["+"] = 20;
    BiOpPrecedence["-"] = 20;
    BiOpPrecedence["*"] = 30;
    BiOpPrecedence["/"] = 30;
}


void Parser::parse() {
    read_Program();
    return ;
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
    read_Args_Decl(tmp);
    token_check_now(Token_kind::L_brace);
    next_token();

    while (true) {
        switch (token_now.kind) {
            case Token_kind::Return:
                next_token();
                tmp->add_stmt(read_Ret_stmt());
                break;
            case Token_kind ::Let:
                next_token();
                tmp->add_stmt(read_Var_init_stmt());
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

void Parser::read_Args_Decl(std::unique_ptr<FUNC_DECL_AST> &f) {
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

std::unique_ptr<EXPR_BASE_AST> Parser::read_Expr() {
    std::unique_ptr<EXPR_BASE_AST> LHS;
    std::unique_ptr<EXPR_BASE_AST> RHS;
    LHS = read_PrimaryExpr();
    while (true) {
        if (token_now.kind != Token_kind::Ope) {
            return LHS;
        } else {
            Token cope = token_now;
            next_token();
            LHS = read_marge_RHS(cope.str, std::move(LHS));
        }
    }
}

std::unique_ptr<EXPR_BASE_AST> Parser::read_marge_RHS(std::string Op, std::unique_ptr<EXPR_BASE_AST> LHS) {
    auto tmp = read_PrimaryExpr();
    auto next_op = token_now;
    if (next_op.kind != Token_kind::Ope) {
        return std::make_unique<EXPR_BI_AST>(Op, std::move(LHS), std::move(tmp));
    } else if (BiOpPrecedence[Op] >= BiOpPrecedence[token_now.str]) {
        return std::make_unique<EXPR_BI_AST>(Op, std::move(LHS), std::move(tmp));
    } else {
        next_token();
        return std::make_unique<EXPR_BI_AST>(Op, std::move(LHS),
                                             std::move(read_marge_RHS(next_op.str, std::move(tmp))));
    }
}

std::unique_ptr<EXPR_BASE_AST> Parser::read_PrimaryExpr() {
    std::unique_ptr<EXPR_BASE_AST> tmp;
    switch (token_now.kind) {
        default:
            return nullptr;
        case Token_kind::Integer_val:
            tmp = std::make_unique<INT_EXPR_AST>(token_now.str);
            next_token();
            return tmp;
        case Token_kind::L_paren:
            next_token();
            tmp = read_Expr();
            token_check_now(Token_kind::R_paren);
            next_token();
            return tmp;
        case Token_kind ::Ident:
            auto name = token_now.str;
            next_token();
            if(token_now.kind==Token_kind::L_paren){
                next_token();
                tmp = std::make_unique<FUNC_EXPR_AST>(std::move(name),std::move(read_Args()));
                return tmp;
            }else{
                tmp = std::make_unique<VAR_EXPR_AST>(std::move(name));
                return tmp;
            }
    }
}

std::vector<std::unique_ptr<EXPR_BASE_AST>> Parser::read_Args() {
    auto tmp = std::vector<std::unique_ptr<EXPR_BASE_AST>>();
    while(token_now.kind!=Token_kind::R_paren){
        tmp.push_back(read_Expr());
        token_check_next(Token_kind::Comma);
        next_token();
    }
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
        std::cout << now_counter << std::endl;
    }
}

void Parser::token_check_next(Token_kind k) {
    next_token();
    token_check_now(k);
}

std::unique_ptr<VAR_INIT_STMT_AST> Parser::read_Var_init_stmt() {
    token_check_now(Token_kind::Ident);
    auto name = token_now.str;
    token_check_next(Token_kind::Colon);
    next_token();
    if(token_now.str=="Int"){
        token_check_next(Token_kind::Eq);
        next_token();
        return std::make_unique<VAR_INIT_STMT_AST>(name,"Int",read_Expr());
    }
    else{
        return nullptr;
    }
}
