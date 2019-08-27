////
//// Created by montyaxn on 8/23/19.
////


#include "llvm/ADT/APFloat.h"
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



llvm::Value *EXPR_BI_AST::generate() {
    if (ope == "+")return Builder.CreateAdd(LHS->generate(), RHS->generate(), "addtmp");
    else if (ope == "-")return Builder.CreateSub(LHS->generate(), RHS->generate(), "subtmp");
    else if (ope == "*")return Builder.CreateMul(LHS->generate(), RHS->generate(), "multmp");
    else return nullptr;

}

Value *INT_EXPR_AST::generate() {
    return ConstantInt::get(TheContext, APInt(32, val, 10));
}

llvm::Value* VAR_EXPR_AST::generate() {
    return nullptr;
}

llvm::Value* FUNC_EXPR_AST::generate() {
    return nullptr;
}

