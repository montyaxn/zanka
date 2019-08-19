//
// Created by montyaxn on 19/06/21.
//

#include "AST.h"
#include <iostream>


DECL_BLOCK_AST::~DECL_BLOCK_AST() {
    for (BASE_AST *d:decls) {
        delete (d);
    }
}

void DECL_BLOCK_AST::show() {
    std::cout << "DECL-BLOCK" << std::endl;
    for (BASE_AST *d : decls) {
        d->show();
    }
    std::cout << "DECL-BLOCK END" << std::endl;
}


void DECL_BLOCK_AST::add_decl(BASE_AST *decl) {
    decls.push_back(decl);
}

PROGRAM_AST::~PROGRAM_AST() {
    delete (decl_block);
}

void PROGRAM_AST::show() {
    std::cout << "PROGRAM-AST" << std::endl;
    decl_block->show();
    std::cout << "PROGRAM-AST END" << std::endl;
}

FUNC_DECL_AST::~FUNC_DECL_AST() {
    for (BASE_AST *s : stmts) {
        delete (s);
    }
}

void FUNC_DECL_AST::show() {
    std::cout << "FUNC-DECL: " << name << std::endl;
    std::cout << "Arg: ";
    for (const ARG &arg : args) {
        std::cout << arg.name << ":" << arg.type << " ";
    }
    std::cout << "-> " << ret_type << std::endl;
    for (BASE_AST *s : stmts) {
        s->show();
    }
    std::cout << "FUNC-DECL END" << std::endl;
}

void FUNC_DECL_AST::add_stmt(BASE_AST *stmt) {
    stmts.push_back(stmt);
}

void FUNC_DECL_AST::add_arg(ARG &arg) {
    args.push_back(arg);
}

void FUNC_DECL_AST::make_ret_type(std::string type) {
    ret_type = std::move(type);
}

RET_STMT_AST::~RET_STMT_AST() {
    delete (expr);
}

void RET_STMT_AST::show() {
    std::cout << "AST-KIND : RETURN-STMT.val = " << expr->val << std::endl;
}

void EXPR_AST::show() {
    std::cout << "AST-KIND : EXPR" << std::endl;
}