cmake_minimum_required(VERSION 3.14)
project(zanka)

set(CMAKE_CXX_STANDARD 14)

add_executable(giuniu main.cpp AST.cpp AST.h Lex.cpp Lex.h Token_def.h Parse.cpp Parse.h)