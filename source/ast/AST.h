//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_AST_H
#define ZANKA_AST_H

#include <string>
#include <vector>
#include <memory>
#include <llvm/IR/Value.h>


class BASE_AST {
private:
public:
    virtual ~BASE_AST() = default;
    virtual llvm::Value * generate() = 0;

};


class DECL_BLOCK_AST : public BASE_AST {
private:
    std::vector<std::unique_ptr<BASE_AST>> decls;
public:


    void add_decl(std::unique_ptr<BASE_AST> decl);

    llvm::Value * generate() override;
};

class PROGRAM_AST : public BASE_AST {
    std::unique_ptr<DECL_BLOCK_AST> decl_block;
public:
    explicit PROGRAM_AST(std::unique_ptr<DECL_BLOCK_AST> decl_block) : decl_block(std::move(decl_block)) {}

    llvm::Value * generate() override;
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

    llvm::Value * generate() override;
};

class EXPR_BASE_AST : public BASE_AST{
};

class EXPR_VALUE_BASE_AST : public EXPR_BASE_AST{

};

class EXPR_AST; // expr_f_ast にて必要

class VAR_EXPR_AST : public EXPR_VALUE_BASE_AST {
    std::string name;
};

class FUNC_EXPR_AST : public EXPR_VALUE_BASE_AST {
    std::string name;
    std::vector<std::unique_ptr<EXPR_AST>> args;
};

class I32_EXPR_AST : public EXPR_VALUE_BASE_AST {
private:
    int val;
public:
    explicit I32_EXPR_AST(int val) : val(val) {}

    llvm::Value * generate() override;
};



//class EXPR_F_AST : public EXPR_BASE_AST {
//private:
//    std::unique_ptr<EXPR_AST> expr;
//    std::unique_ptr<EXPR_BASE_AST> val;
//public:
//    explicit EXPR_F_AST(std::unique_ptr<EXPR_AST> expr) : val(nullptr), expr(std::move(expr)) {}
//
//    explicit EXPR_F_AST(std::unique_ptr<EXPR_BASE_AST> val) : expr(nullptr),val(std::move(val)) {}
//
//    llvm::Value *generate() override;
//};

//enum Ope {
//    Plus,
//    Minus,
//    Mult,
//    Div
//};


//class EXPR_T_DASH_AST : public EXPR_BASE_AST {
//private:
//    std::unique_ptr<EXPR_T_DASH_AST> term = nullptr;
//    std::unique_ptr<EXPR_F_AST> fuct = nullptr;
//    Ope ope = Mult;
//public:
//    EXPR_T_DASH_AST(Ope ope,std::unique_ptr<EXPR_F_AST> fuct) : fuct(std::move(fuct)), ope(ope) {}
//
//    EXPR_T_DASH_AST(Ope ope,std::unique_ptr<EXPR_T_DASH_AST> term, std::unique_ptr<EXPR_F_AST> fuct) : term(
//            std::move(term)), fuct(std::move(fuct)), ope(ope) {}
//    Ope get_ope();
//    llvm::Value *generate() override;
//};
//
//class EXPR_T_AST : public EXPR_BASE_AST {
//private:
//    std::unique_ptr<EXPR_F_AST> fuct;
//    std::unique_ptr<EXPR_T_DASH_AST> term = nullptr;
//public:
//    explicit EXPR_T_AST(std::unique_ptr<EXPR_F_AST> fuct) : fuct(std::move(fuct)){}
//
//    EXPR_T_AST( std::unique_ptr<EXPR_F_AST> fuct,std::unique_ptr<EXPR_T_DASH_AST> term) : term(
//            std::move(term)), fuct(std::move(fuct)) {}
//
//    llvm::Value *generate() override;
//};
//
//class EXPR_DASH_AST : public EXPR_BASE_AST {
//private:
//    std::unique_ptr<EXPR_T_AST> term = nullptr;
//    std::unique_ptr<EXPR_DASH_AST> expr = nullptr;
//    Ope ope = Plus;
//public:
//    EXPR_DASH_AST(Ope ope,std::unique_ptr<EXPR_T_AST> term) : term(std::move(term)), ope(ope) {}
//
//    EXPR_DASH_AST(Ope ope,std::unique_ptr<EXPR_T_AST> term, std::unique_ptr<EXPR_DASH_AST> expr) : term(
//            std::move(term)), expr(std::move(expr)), ope(ope) {}
//    Ope get_ope();
//    llvm::Value *generate() override;
//};

//class EXPR_AST : public EXPR_BASE_AST {
//private:
//    std::unique_ptr<EXPR_T_AST> term;
//    std::unique_ptr<EXPR_DASH_AST> expr;
//public:
//    explicit EXPR_AST(std::unique_ptr<EXPR_T_AST> term) : term(std::move(term)) {}
//
//    EXPR_AST(std::unique_ptr<EXPR_T_AST> term, std::unique_ptr<EXPR_DASH_AST> expr) : term(std::move(term)),
//                                                                                      expr(std::move(expr)) {}
//
//    llvm::Value *generate() override;
//};

class EXPR_AST : public EXPR_BASE_AST {
    std::string ope;
    std::unique_ptr<EXPR_BASE_AST> LHS, RHS;

public:

    EXPR_AST(std::string ope, std::unique_ptr<EXPR_BASE_AST> LHS,
                  std::unique_ptr<EXPR_BASE_AST> RHS)
            : ope(std::move(ope)), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};


class RET_STMT_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_BASE_AST> expr;
public:
    void make_expr(std::unique_ptr<EXPR_BASE_AST> e);

    llvm::Value *generate() override;
};

#endif //ZANKA_AST_H
