//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_TOKEN_DEF_H
#define ZANKA_TOKEN_DEF_H

#include "Type_def.h"

enum class Token_kind {
    Ident,
    Let,
    Integer_val,
//    Decimal_val,
//    Char_val,
//    String_val,
    Map,
//    Expr,
//    MutMap,
    Return,
    Colon,
    Comma,
    Eq,
    Period,
    Semi_colon,
    Ope,
    R_paren,
    L_paren,
    R_brace,
    L_brace,
    Arrow,
    End,
    Other,
};

struct Token {
    Token_kind kind;
    std::string str = "";
};

enum class Char_kind {
    White,
    New_line,
    Letter,
    Digit,
    Colon,
    Semi_colon,
    Comma,
    Period,
    Plus,
    Minus,
    Mult,
    Div,
    Less,
    Gtr,
    Eq,
    R_paren,
    L_paren,
    R_brace,
    L_brace,
    End_of_file,
    Other,
};

#endif //ZANKA_TOKEN_DEF_H
