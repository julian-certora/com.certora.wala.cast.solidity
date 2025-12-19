//
//  translator.h
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//

#include "solidityBridge.h"
using namespace solidity::frontend;

class Translator : public ASTConstVisitor {
public:
    virtual bool visitNode(ASTNode const&) override;

    virtual bool visit(const SourceUnit &_node) override;
    
    virtual bool visit(const ContractDefinition &_node) override;
};
