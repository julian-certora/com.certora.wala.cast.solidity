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
    jobject n = cast.makeConstant( _node.name().c_str() );
    jclass obj = jniEnv->FindClass("java/lang/Object");
    jmethodID toString = jniEnv->GetMethodID(obj, "toString", "()Ljava/lang/String;");
    std::cout << "contract " <<  jniEnv->GetStringUTFChars((jstring)jniEnv->CallObjectMethod(n, toString), 0) << std::endl;
     return true;
}
