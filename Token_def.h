//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_TOKEN_DEF_H
#define ZANKA_TOKEN_DEF_H

enum class Token_kind{
    Ident,
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
    Period,
    Semi_colon,
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
