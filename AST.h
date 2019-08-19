//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_AST_H
#define ZANKA_AST_H

#include <string>
#include <vector>

enum class AST_kind {
    program_block_AST,
    decl_block_AST,
    func_decl_AST,
    ret_stmt_AST,
    expr_AST,
//    if_stmt_AST,
//    loop_stmt_AST,  TODO but DO step by step
};

class BASE_AST {
private:
    const AST_kind kind;
public:
    explicit BASE_AST(AST_kind k) : kind(k) {}
    virtual ~BASE_AST() = default;
    virtual void show() = 0;
};


class DECL_BLOCK_AST : public BASE_AST {
private:
    std::vector<BASE_AST *> decls;
public:
    DECL_BLOCK_AST():BASE_AST(AST_kind::decl_block_AST){}
    ~DECL_BLOCK_AST() override ;
    void show() override;

    void add_decl(BASE_AST *decl);
};

class PROGRAM_AST : public BASE_AST {
private:

public:
    DECL_BLOCK_AST* decl_block = new DECL_BLOCK_AST();
    PROGRAM_AST() :BASE_AST(AST_kind::program_block_AST){}
    ~PROGRAM_AST() override ;

    void show() override;
};

struct ARG{
    std::string name = "";
    std::string type = "";
};

class FUNC_DECL_AST : public BASE_AST {
private:
    std::vector<BASE_AST *> stmts;
    std::vector<ARG> args;
    std::string ret_type;
public:
    FUNC_DECL_AST() : BASE_AST(AST_kind::func_decl_AST){}
    ~FUNC_DECL_AST() override ;
    void show() override;

    void add_stmt(BASE_AST *stmt);
    void add_arg(ARG& arg);
    void make_ret_type(std::string type);
    std::string name = "";
};




class EXPR_AST : public BASE_AST {
private:
public:
    EXPR_AST():BASE_AST(AST_kind::expr_AST){}
    int val = 0;
    void show() override;
};

class RET_STMT_AST : public BASE_AST {
private:

public:
    RET_STMT_AST():BASE_AST(AST_kind::ret_stmt_AST){}
    ~RET_STMT_AST() override ;
    void show() override;
    EXPR_AST* expr = new EXPR_AST();
};

#endif //ZANKA_AST_H
