//
// Created by montyaxn on 8/24/19.
//

#ifndef ZANKA_TABLE_H
#define ZANKA_TABLE_H

#include <map>
#include <vector>
#include "llvm/IR/Value.h"

class Table {
public:
    std::vector<std::map<std::string,llvm::Value*>> nameTable;
//    std::vector<std::map<std::string>> typeTable;
};


#endif //ZANKA_TABLE_H
