//
// Created by montyaxn on 8/23/19.
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
using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value *> NamedValues;

Value* PROGRAM_AST::generate() {
    decl_block->generate();
}

Value* DECL_BLOCK_AST::generate() {
    for(auto &d : decls){
        d->generate();
    }
}

Value* FUNC_DECL_AST::generate() {

}

llvm::Value* RET_STMT_AST::generate() {
    return Builder.CreateRet(expr->generate());
}

//llvm::Value* EXPR_AST::generate() {
//    if(expr== nullptr){
//        return term->generate();
//    }else{
//        switch (expr->get_ope()){
//            case Plus:
//                return Builder.CreateAdd(term->generate(),expr->generate(),"addtmp");
//            case Minus:
//                return Builder.CreateSub(term->generate(),expr->generate(),"subtmp");
//            default:
//                return nullptr;
//        }
//    }
//}
//
//llvm::Value* EXPR_DASH_AST::generate() {
//    if(expr== nullptr){
//        return term->generate();
//    }else{
//        switch (expr->get_ope()){
//            case Plus:
//                return Builder.CreateAdd(term->generate(),expr->generate(),"addtmp");
//            case Minus:
//                return Builder.CreateSub(term->generate(),expr->generate(),"subtmp");
//            default:
//                return nullptr;
//        }
//    }
//}
//
//llvm::Value* EXPR_T_AST::generate() {
//    if(term== nullptr){
//        return fuct->generate();
//    }else{
//        switch (term->get_ope()){
//            case Mult:
//                return Builder.CreateMul(fuct->generate(),term->generate(),"multmp");
//            default:
//                return nullptr;
//        }
//    }
//}
//
//
//
//Value* EXPR_T_DASH_AST::generate() {
//    if(term==nullptr){
//        return fuct->generate();
//    }else{
//        switch (term->get_ope()){
//            case Mult:
//                return Builder.CreateMul(term->generate(),fuct->generate(),"multmp");
//            default:
//                return nullptr;
//        }
//    }
//}
//
//
//
//
//Value* EXPR_F_AST::generate() {
//    if(expr== nullptr){
//        return val->generate();
//    }else{
//        return expr->generate();
//    }
//}



Value* I32_EXPR_AST::generate() {
    return ConstantInt::get(TheContext,APInt(32,val));
}

