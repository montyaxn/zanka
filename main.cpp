#include <iostream>
#include <fstream>
#include "Lex.h"
#include "Parse.h"



int main(int argc,char** argv) {
    if(argc != 2) {
        std::cout << "Usage: giuniu file" << std::endl;
    }
    std::ifstream ifs(argv[1]);
    if(ifs.fail()) std::cout << "Error: can't find the file" << std::endl;
    std::string target((std::istreambuf_iterator<char>(ifs)),
                    std::istreambuf_iterator<char>());
    Lex lex(target);
    Parser parser(lex.tokenize());
    parser.test_lex();
    parser.parse();
    parser.test_parse();
}