//
// Created by montyaxn on 19/06/21.
//

#include "AST.h"
//#include "llvm/ADT/APFloat.h"
//#include "llvm/ADT/STLExtras.h"
//#include "llvm/IR/BasicBlock.h"
//#include "llvm/IR/Constants.h"
//#include "llvm/IR/DerivedTypes.h"
//#include "llvm/IR/Function.h"
//#include "llvm/IR/IRBuilder.h"
//#include "llvm/IR/LLVMContext.h"
//#include "llvm/IR/Module.h"
//#include "llvm/IR/Type.h"
//#include "llvm/IR/Verifier.h"
#include <vector>


void DECL_BLOCK_AST::add_decl(std::unique_ptr<BASE_AST> decl) {
    decls.push_back(std::move(decl));
}

void FUNC_DECL_AST::add_stmt(std::unique_ptr<BASE_AST> stmt) {
    stmts.push_back(std::move(stmt));
}

void FUNC_DECL_AST::add_arg(ARG &arg) {
    args.push_back(arg);
}

void FUNC_DECL_AST::make_ret_type(std::string type) {
    ret_type = std::move(type);
}


void RET_STMT_AST::make_expr(std::unique_ptr<EXPR_BASE_AST> e) {
    expr = std::move(e);
}


