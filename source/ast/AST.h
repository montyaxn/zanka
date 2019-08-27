//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_AST_H
#define ZANKA_AST_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <llvm/IR/Value.h>
#include "AST.h"

using namespace llvm;


class BASE_AST {
private:
public:
    virtual ~BASE_AST() = default;

};


class DECL_BLOCK_AST : public BASE_AST {
private:
    std::vector<std::unique_ptr<BASE_AST>> decls;
public:


    void add_decl(std::unique_ptr<BASE_AST> decl);


};

class PROGRAM_AST : public BASE_AST {
    std::unique_ptr<DECL_BLOCK_AST> decl_block;
public:
    explicit PROGRAM_AST(std::unique_ptr<DECL_BLOCK_AST> decl_block) : decl_block(std::move(decl_block)) {}

};


struct ARG {
    std::string name = "";
    std::string type = "";
};

class FUNC_DECL_AST : public BASE_AST {
private:
    std::vector<std::unique_ptr<BASE_AST>> stmts;
    std::vector<ARG> args;
    std::string ret_type;
public:

    void add_stmt(std::unique_ptr<BASE_AST>);

    void add_arg(ARG &arg);

    void make_ret_type(std::string type);

    std::string name = "";

};

class EXPR_BASE_AST : public BASE_AST{
public:
    virtual llvm::Value* generate() = 0;
};

class EXPR_VALUE_BASE_AST : public EXPR_BASE_AST{

};


class VAR_EXPR_AST : public EXPR_VALUE_BASE_AST {
public:
    explicit VAR_EXPR_AST( std::string name) : name(std::move(name)){}
    llvm::Value* generate() override;
private:
    std::string name;
};

class FUNC_EXPR_AST : public EXPR_VALUE_BASE_AST {
public:
    FUNC_EXPR_AST(std::string callee, std::vector<std::unique_ptr<EXPR_BASE_AST>> args) : callee(std::move(callee)),args(std::move(args)){}

private:
    llvm::Value* generate() override;
    std::string callee;
    std::vector<std::unique_ptr<EXPR_BASE_AST>> args;
};

class INT_EXPR_AST : public EXPR_VALUE_BASE_AST {
private:
    std::string val;
public:
    explicit INT_EXPR_AST(std::string val) : val(std::move(val)) {}

    llvm::Value * generate() override;
};

class EXPR_BI_AST : public EXPR_BASE_AST {
    std::string ope;
    std::unique_ptr<EXPR_BASE_AST> LHS, RHS;

public:
    llvm::Value* generate() override;
    EXPR_BI_AST(std::string ope, std::unique_ptr<EXPR_BASE_AST> LHS,
                  std::unique_ptr<EXPR_BASE_AST> RHS)
            : ope(std::move(ope)), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};


class RET_STMT_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_BASE_AST> expr;
public:
    void make_expr(std::unique_ptr<EXPR_BASE_AST> e);

};

class VAR_INIT_STMT_AST : public BASE_AST{
private:
    std::string name;
    std::string type;
    std::unique_ptr<EXPR_BASE_AST> expr;
public:
    VAR_INIT_STMT_AST(std::string n,std::string t,std::unique_ptr<EXPR_BASE_AST> e):name(std::move(n)),type(std::move(t)),expr(std::move(e)){}

};

#endif //ZANKA_AST_H
