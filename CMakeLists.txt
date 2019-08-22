cmake_minimum_required(VERSION 3.14)
project(zanka)

set(CMAKE_CXX_STANDARD 14)

add_executable(giuniu source/main.cpp source/ast/AST.cpp source/ast/AST.h source/parser/lexer/Lex.cpp source/parser/lexer/Lex.h source/Token_def.h source/parser/Parse.cpp source/parser/Parse.h source/Type_def.h source/code_gen/code_gen.cpp source/code_gen/code_gen.h)