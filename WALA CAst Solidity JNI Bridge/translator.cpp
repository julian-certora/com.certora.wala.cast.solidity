//
//  translator.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//
#include "translator.h"
#include "CAstWrapper.h"

bool Translator::visitNode(ASTNode const&_node) {
    std::cout << _node.location() << std::endl;
    return false;
}

