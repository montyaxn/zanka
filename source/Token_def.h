//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_TOKEN_DEF_H
#define ZANKA_TOKEN_DEF_H

#include "Type_def.h"

enum class Token_kind{
    Ident,
    val_bear,
    Integer_val,
//    Decimal_val,
//    Char_val,
//    String_val,
    token_bear,
    Map,
//    Expr,
//    MutMap,
    Return,
    Colon,
    Comma,
    Period,
    Semi_colon,
    ope_bear,
    Plus,
    Minus,
    Mult,
    Div,
    Less,
    Gtr,
    Leq,
    GtrEq,
    Eq,
    R_paren,
    L_paren,
    R_brace,
    L_brace,
    Arrow,
    end_bear,
    End,
    Other,
};

struct Token{
    Token_kind kind;
    int val =0;
    std::string str = "";
};

enum class Char_kind{
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
