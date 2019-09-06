//
// Created by montyaxn on 9/6/19.
//

#ifndef ZANKA_LLVM_STATIC_DECL_H
#define ZANKA_LLVM_STATIC_DECL_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include <map>

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value *> NamedValues;


#endif //ZANKA_LLVM_STATIC_DECL_H
