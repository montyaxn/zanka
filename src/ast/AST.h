//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_AST_H
#define ZANKA_AST_H


#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"


#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "AST.h"

#include "../llvm_static_decl.h"


using namespace llvm;


Type* get_llvm_Vty_byName(const std::string &ty_name);


class BASE_AST {
private:
public:
    virtual ~BASE_AST() = default;
};

enum class Decl_kind {
    Func,
};

class BASE_DECL_AST : public BASE_AST {
public:
    Decl_kind kind;
};


class DECL_BLOCK_AST : public BASE_AST {
private:
    std::vector<std::shared_ptr<BASE_DECL_AST>> decls;
public:

    void add_decl(std::shared_ptr<BASE_DECL_AST> decl);

    void generate();
};


class PROGRAM_AST : public BASE_AST {
    std::unique_ptr<DECL_BLOCK_AST> decl_block;
public:
    explicit PROGRAM_AST(std::unique_ptr<DECL_BLOCK_AST> decl_block) : decl_block(std::move(decl_block)) {}

    void generate();
};


class EXPR_BASE_AST : public BASE_AST {
public:
    virtual Value *generate() = 0;
};

class VAR_EXPR_AST : public EXPR_BASE_AST {
public:
//    VAR_EXPR_AST(std::string name,Literal_kind ty);
//    VAR_EXPR_AST(std::string name,std::string ty_name);

    VAR_EXPR_AST(std::string n) : name(std::move(n)) {}

    Value *generate() override;

private:

    std::string name;
};

class FUNC_EXPR_AST : public EXPR_BASE_AST {
public:
    FUNC_EXPR_AST(std::string callee, std::vector<std::unique_ptr<EXPR_BASE_AST>> args) : callee(std::move(callee)),
                                                                                          args(std::move(args)) {}

private:
    Value *generate() override;

    std::string callee;
    std::vector<std::unique_ptr<EXPR_BASE_AST>> args;
};

class INT_EXPR_AST : public EXPR_BASE_AST {
private:
    std::string str;
    uint8_t radix;
public:
    explicit INT_EXPR_AST(std::string s,uint8_t rad) : str(std::move(s)) , radix(rad){}

    Value *generate() override;
};

class CHAR_EXPR_AST : public EXPR_BASE_AST {
private:
    char val;
public:
    explicit CHAR_EXPR_AST(std::string val) : val(std::move(val[0])) {}

    Value *generate() override;
};

class STRING_EXPR_AST : public EXPR_BASE_AST {
private:
    std::string val;
public:
    explicit STRING_EXPR_AST(std::string val) : val(std::move(val)) {}

    Value *generate() override;
};

class EXPR_BI_AST : public EXPR_BASE_AST {
    std::string ope;
    std::shared_ptr<EXPR_BASE_AST> LHS, RHS;

public:
    Value *generate() override;

    EXPR_BI_AST(std::string ope, std::shared_ptr<EXPR_BASE_AST> LHS,
                std::shared_ptr<EXPR_BASE_AST> RHS)
            : ope(std::move(ope)), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

enum class Stmt_kind {
    RET,
    VAR
};

class STMT_BASE_AST : public BASE_AST {
public:
    Stmt_kind kind;
};

class RET_STMT_AST : public STMT_BASE_AST {
private:

public:
    void make_expr(std::unique_ptr<EXPR_BASE_AST> e);

    std::unique_ptr<EXPR_BASE_AST> expr;

    RET_STMT_AST() { this->kind = Stmt_kind::RET; }
};

class VAR_INIT_STMT_AST : public STMT_BASE_AST {
private:

    std::string name;
    std::string type;
    std::unique_ptr<EXPR_BASE_AST> expr;
public:
    VAR_INIT_STMT_AST(std::string n, std::string t, std::unique_ptr<EXPR_BASE_AST> e) : name(std::move(n)),
                                                                                        type(std::move(t)),
                                                                                        expr(std::move(e)) {
        this->kind = Stmt_kind::VAR;
    }

};

struct ARG {
    std::string name = "";
    std::string type;
};

class FUNC_DECL_AST : public BASE_DECL_AST {
private:
    std::vector<std::shared_ptr<STMT_BASE_AST>> stmts;
    std::vector<ARG> args;
    std::string ret_type = "";
public:
    FUNC_DECL_AST() { kind = Decl_kind::Func; }

    void add_stmt(std::shared_ptr<STMT_BASE_AST>);

    void add_arg(ARG &arg);

    void make_ret_type(std::string type);

    std::string name = "";

    Function *generate();
};


#endif //ZANKA_AST_H
