//
// Created by montyaxn on 19/06/21.
//

#ifndef ZANKA_LEX_H
#define ZANKA_LEX_H

#include <iostream>
#include <string>
#include <vector>
#include "../../Token_def.h"
#include "../../Type_def.h"

class Lex {
private:
    std::string target;
    Char_kind charKind_T[256] = {};
    const int file_length;
    int pos = 0;
    char ch =' ';
    Char_kind ck = Char_kind::Other;

    void next_char();
    void make_charKind_T();

public:
    explicit Lex(std::string file);

    std::vector<Token> tokenize();

    int now_column = 0;
    int now_row = 0;

};


#endif //ZANKA_LEX_H
