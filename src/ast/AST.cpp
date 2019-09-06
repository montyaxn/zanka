//
// Created by montyaxn on 19/06/21.
//

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

#include "AST.h"
#include <vector>
#include <iostream>

//
//VAR_EXPR_AST::VAR_EXPR_AST(std::string name, Literal_kind ty) : name(std::move(name)) {
//    switch (ty) {
//        case Literal_kind::I32 :
//            type = Type::getInt32Ty(TheContext);
//
//        case Literal_kind::I8 :
//            type = Type::getInt8Ty(TheContext);
//
//        case Literal_kind::I64 :
//            type = Type::getInt64Ty(TheContext);
//        case Literal_kind::Char:
//            type = Type::getInt8Ty(TheContext);
//        case Literal_kind::I1:
//            type = Type::getInt1Ty(TheContext);
//        default:
//            std::cout << "unknown type" << std::endl;
//            type = nullptr;
//
//    }
//}

//VAR_EXPR_AST::VAR_EXPR_AST(std::string name, std::string ty_name) : name(std::move(name)) {
//
//}
// TODO structure が実装されたらここも実装する

void DECL_BLOCK_AST::add_decl(std::shared_ptr<BASE_DECL_AST> decl) {
    decls.push_back(decl);
}

void FUNC_DECL_AST::add_stmt(std::shared_ptr<STMT_BASE_AST> stmt) {
    stmts.push_back(stmt);
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
