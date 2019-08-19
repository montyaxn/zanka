//
// Created by montyaxn on 19/06/21.
//

#include "Lex.h"

Lex::Lex(std::string file) : file_length(file.length()) {
    target = std::move(file);
    make_charKind_T();
    next_char();
}

void Lex::make_charKind_T() {
    for (int i = 0; i < 256; i++) {
        charKind_T[i] = Char_kind::Other;
    }

    //Whites
    charKind_T[' '] = Char_kind::White;
    charKind_T['\t'] = Char_kind::White;
    charKind_T['\n'] = Char_kind::New_line;

    //Letters
    for (char c = 'a'; c <= 'z'; c++) {
        charKind_T[c] = Char_kind::Letter;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        charKind_T[c] = Char_kind::Letter;
    }
    charKind_T['_'] = Char_kind::Letter;

    //Digits
    for (char c = '0'; c <= '9'; c++) {
        charKind_T[c] = Char_kind::Digit;
    }

    //Symbols
    charKind_T[':'] = Char_kind::Colon;
    charKind_T[';'] = Char_kind::Semi_colon;
    charKind_T[','] = Char_kind::Comma;
    charKind_T['.'] = Char_kind::Period;
    charKind_T['+'] = Char_kind::Plus;
    charKind_T['-'] = Char_kind::Minus;
    charKind_T['*'] = Char_kind::Mult;
    charKind_T['/'] = Char_kind::Div;
    charKind_T['<'] = Char_kind::Less;
    charKind_T['>'] = Char_kind::Gtr;
    charKind_T['='] = Char_kind::Eq;
    charKind_T['('] = Char_kind::L_paren;
    charKind_T[')'] = Char_kind::R_paren;
    charKind_T['{'] = Char_kind::L_brace;
    charKind_T['}'] = Char_kind::R_brace;
}

void Lex::next_char() {
    if (pos >= file_length) {
        ch = -1;
        ck = Char_kind::End_of_file;
    } else {
        ch = target[pos];
        ck = charKind_T[ch];
        if (ch == '\n') {
            now_row = 0;
            now_column++;
        } else {
            now_row++;
        }
        pos++;
    }
}

std::vector<Token> Lex::tokenize() {
    std::vector<Token> tokens;
    while (ck != Char_kind::End_of_file) {
        Token tmp;
        while (ck == Char_kind::White or ck == Char_kind::New_line) {
            next_char();
        }

        switch (ck) {
            case Char_kind::Letter:
                while (ck == Char_kind::Letter or ck == Char_kind::Digit) {
                    tmp.str += ch;
                    next_char();
                }
                if (tmp.str == "map") {
                    tmp.kind = Token_kind::Map;
                } else if (tmp.str == "return") {
                    tmp.kind = Token_kind::Return;
                } else {
                    tmp.kind = Token_kind::Ident;
                }
                break;

            case Char_kind::Digit:
                tmp.val = ch - '0';
                next_char();
                while (ck == Char_kind::Digit) {
                    tmp.val = (tmp.val * 10) + (ch - '0');
                    next_char();
                }
                tmp.kind = Token_kind::Integer_val;
                break;

            case Char_kind::Colon:
                tmp.kind = Token_kind::Colon;
                next_char();
                break;

            case Char_kind::Semi_colon:
                tmp.kind = Token_kind::Semi_colon;
                next_char();
                break;
            case Char_kind::L_paren:
                tmp.kind = Token_kind::L_paren;
                next_char();
                break;
            case Char_kind::R_paren:
                tmp.kind = Token_kind::R_paren;
                next_char();
                break;
            case Char_kind::L_brace:
                tmp.kind = Token_kind::L_brace;
                next_char();
                break;
            case Char_kind::R_brace:
                tmp.kind = Token_kind::R_brace;
                next_char();
                break;
            case Char_kind::Comma:
                tmp.kind = Token_kind::Comma;
                next_char();
                break;
            case Char_kind::Period:
                tmp.kind = Token_kind::Period;
                next_char();
                break;
            case Char_kind ::Plus:
                tmp.kind = Token_kind ::Plus;
                next_char();
                break;
            case Char_kind ::Minus:
                next_char();
                if(ck==Char_kind::Gtr){
                    tmp.kind=Token_kind ::Arrow;
                    next_char();
                } else{
                    tmp.kind=Token_kind ::Minus;
                }
                break;
            case Char_kind ::Mult:
                tmp.kind=Token_kind ::Mult; //*
                next_char();
                break;
            case Char_kind ::Div:
                tmp.kind=Token_kind ::Div; // /
                next_char();
                break;
            case Char_kind::Eq:
                next_char();
                if(ck==Char_kind::Eq) {
                    tmp.kind = Token_kind::Eq; //==
                    next_char();
                } else{
                    tmp.kind=Token_kind::Other;
                }
                break;
            case Char_kind ::Less:
                next_char();
                if(ck==Char_kind::Eq){
                    tmp.kind = Token_kind ::Leq;
                    next_char();
                } else{
                    tmp.kind = Token_kind ::Less;
                }
                break;
            case Char_kind ::Gtr:
                next_char();
                if(ck == Char_kind::Eq){
                    tmp.kind = Token_kind ::GtrEq;
                    next_char();
                } else{
                    tmp.kind = Token_kind ::Gtr;
                }
                break;

            case Char_kind::End_of_file:
                tmp.kind = Token_kind::End;

            default:
                tmp.kind = Token_kind::Other;
                std::cout << "Error!!  '" << ch << "' is not recognized" << std::endl;
                next_char();
        }
        tokens.push_back(tmp);
    }
    Token tmp;
    tmp.kind = Token_kind::End;
    tokens.push_back(tmp);
    return std::move(tokens);
}