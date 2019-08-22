//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_AST_H
#define ZANKA_AST_H

#include <string>
#include <vector>
#include <memory>


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

class VALUE_AST : BASE_AST {

};


class VAR_EXPR_AST : public VALUE_AST {
    std::string name;
};

class FUNC_EXPR_AST : public VALUE_AST {
    std::string name;
    std::vector<ARG> args;
};

class I32_EXPR_AST : public VALUE_AST {
private:
    int val;
public:
    explicit I32_EXPR_AST(int val) : val(val) {}
};

class EXPR_AST; // expr_f_ast にて必要

class EXPR_F_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_AST> expr;
    std::unique_ptr<VALUE_AST> val;
public:
    explicit EXPR_F_AST(std::unique_ptr<EXPR_AST> expr) : val(nullptr), expr(std::move(expr)) {}

    explicit EXPR_F_AST(std::unique_ptr<VALUE_AST> val) : expr(nullptr),val(std::move(val)) {}

};

enum Ope {
    Plus,
    Minus,
    Mult,
    Div
};


class EXPR_T_DASH_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_T_DASH_AST> term = nullptr;
    std::unique_ptr<EXPR_F_AST> fuct = nullptr;
    Ope ope = Mult;
public:
    EXPR_T_DASH_AST(Ope ope,std::unique_ptr<EXPR_F_AST> fuct) : fuct(std::move(fuct)), ope(ope) {}

    EXPR_T_DASH_AST(Ope ope,std::unique_ptr<EXPR_T_DASH_AST> term, std::unique_ptr<EXPR_F_AST> fuct) : term(
            std::move(term)), fuct(std::move(fuct)), ope(ope) {}

};

class EXPR_T_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_F_AST> fuct;
    std::unique_ptr<EXPR_T_DASH_AST> term = nullptr;
public:
    explicit EXPR_T_AST(std::unique_ptr<EXPR_F_AST> fuct) : fuct(std::move(fuct)){}

    EXPR_T_AST( std::unique_ptr<EXPR_F_AST> fuct,std::unique_ptr<EXPR_T_DASH_AST> term) : term(
            std::move(term)), fuct(std::move(fuct)) {}

};

class EXPR_DASH_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_T_AST> term = nullptr;
    std::unique_ptr<EXPR_DASH_AST> expr = nullptr;
    Ope ope = Plus;
public:
    EXPR_DASH_AST(Ope ope,std::unique_ptr<EXPR_T_AST> term) : term(std::move(term)), ope(ope) {}

    EXPR_DASH_AST(Ope ope,std::unique_ptr<EXPR_T_AST> term, std::unique_ptr<EXPR_DASH_AST> expr) : term(
            std::move(term)), expr(std::move(expr)), ope(ope) {}
};

class EXPR_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_T_AST> term;
    std::unique_ptr<EXPR_DASH_AST> expr;
public:
    explicit EXPR_AST(std::unique_ptr<EXPR_T_AST> term) : term(std::move(term)) {}

    EXPR_AST(std::unique_ptr<EXPR_T_AST> term, std::unique_ptr<EXPR_DASH_AST> expr) : term(std::move(term)),
                                                                                      expr(std::move(expr)) {}

};

class RET_STMT_AST : public BASE_AST {
private:
    std::unique_ptr<EXPR_AST> expr;
public:
    void make_expr(std::unique_ptr<EXPR_AST> e);
};

#endif //ZANKA_AST_H
