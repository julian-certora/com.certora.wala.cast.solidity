//
//  translator.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//
#include "translator.h"
#include "CAstWrapper.h"

bool Translator::visitNode(ASTNode const&_node) {
    std::cout << _node.location() << " " << _node.id() << std::endl;
    return true;
}

bool Translator::visit(const SourceUnit &_node) {
    std::vector<ASTPointer<ASTNode>> nodes = _node.nodes();
    for (std::vector<ASTPointer<ASTNode>>::iterator t=nodes.begin();                  t!=nodes.end();
         ++t)
    {
        t->get()->accept(*this);
    }
    return true;
}

bool Translator::visit(const ContractDefinition &_node) {
    std::cout << "contract " <<_node.name() << std::endl;
    return true;
}
