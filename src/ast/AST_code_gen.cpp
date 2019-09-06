////
//// Created by montyaxn on 8/23/19.
////



#include <iostream>
#include "AST.h"

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

#include "../llvm_static_decl.h"



using namespace llvm;

Type* get_llvm_Vty_byName(const std::string &ty_name) {
    if(ty_name=="I32"){
        return Type::getInt32Ty(TheContext);
    }else if(ty_name=="I64"){
        return Type::getInt64Ty(TheContext);
    }else if(ty_name=="Char"){
        return Type::getInt8Ty(TheContext);
    }else{
        return nullptr;
    }
}




void PROGRAM_AST::generate() {
    TheModule = std::make_unique<Module>("zanka", TheContext);
    decl_block->generate();
    TheModule->print(errs(), nullptr);
}

void DECL_BLOCK_AST::generate() {
    for (auto &d : decls) {
        std::shared_ptr<FUNC_DECL_AST> f;
        switch (d->kind) {
            case Decl_kind::Func:
                f = std::static_pointer_cast<FUNC_DECL_AST>(d);
                f->generate();
                break;
        }
    }
}


llvm::Value *EXPR_BI_AST::generate() {
    if (ope == "+")return Builder.CreateAdd(LHS->generate(), RHS->generate(), "addtmp");
    else if (ope == "-")return Builder.CreateSub(LHS->generate(), RHS->generate(), "subtmp");
    else if (ope == "*")return Builder.CreateMul(LHS->generate(), RHS->generate(), "multmp");
    else return nullptr;

}

Value *INT_EXPR_AST::generate() {
    auto tmp = ConstantInt::get(TheContext,APInt(32,StringRef(str),10));
    return tmp;
}

Value *CHAR_EXPR_AST::generate() {
    auto tmp = ConstantInt::get(TheContext,APInt(8,(int)val,false));
    return tmp;
}

Value *STRING_EXPR_AST::generate() {

    return nullptr;
}

llvm::Value *VAR_EXPR_AST::generate() {
    Value *value = NamedValues[name];
    if (!value) return nullptr;
    return value;
}


Value *FUNC_EXPR_AST::generate() {
    // Look up the name in the global module table.
    Function *CalleeF = TheModule->getFunction(callee);

    if (CalleeF->arg_size() != args.size())
        return nullptr;

    std::vector<Value *> argsV;
    for (unsigned i = 0, e = args.size(); i != e; ++i) {
        argsV.push_back(args[i]->generate());
        if (!argsV.back())
            return nullptr;
    }

    return Builder.CreateCall(CalleeF, argsV, "calltmp");
}

Function *FUNC_DECL_AST::generate() {
    std::vector<Type *> arg_types(args.size());

    for(int i = 0 ; i < args.size();i++){
        arg_types[i] = get_llvm_Vty_byName(args[i].type);
    }



    FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), arg_types, false);
    Function *F = Function::Create(FT, Function::ExternalLinkage, name, TheModule.get());
    unsigned Idx = 0;
    for (auto &Arg : F->args())
        Arg.setName(args[Idx++].name);

    BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
    Builder.SetInsertPoint(BB);
    NamedValues.clear();

    for (auto &Arg : F->args())
        NamedValues[Arg.getName()] = &Arg;

    for (auto &stmt:stmts) {
        std::shared_ptr<RET_STMT_AST> ret_stmt;
        switch (stmt->kind) {
            case Stmt_kind::RET:
                ret_stmt = std::static_pointer_cast<RET_STMT_AST>(stmt);
                Builder.CreateRet(ret_stmt->expr->generate());
                break;
            case Stmt_kind::VAR:
                break;
        }
    }
    return F;
}