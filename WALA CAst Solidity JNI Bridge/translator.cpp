//
//  translator.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//
#include "translator.h"
#include "CAstWrapper.h"

bool Translator::visitNode(ASTNode const&_node) {
    std::cout << _node.location() << " " << _node.id() << " " << typeid(_node).name() << std::endl;
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
    std::cout 
        << "contract "
        <<  jniEnv->GetStringUTFChars((jstring)jniEnv->CallObjectMethod(n, toString), 0)
        << std::endl;
     return true;
}

bool Translator::visit(const Assignment &_node) {
    return visitNode(_node);
}

bool Translator::visit(const BinaryOperation &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Block &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ElementaryTypeName &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ElementaryTypeNameExpression &_node) {
    return visitNode(_node);
}

bool Translator::visit(const EmitStatement &_node) {
    return visitNode(_node);
}

bool Translator::visit(const EventDefinition &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ExpressionStatement &_node) {
    return visitNode(_node);
}

bool Translator::visit(const FunctionCall &_node) {
    return visitNode(_node);
}

bool Translator::visit(const FunctionDefinition &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Identifier &_node) {
    return visitNode(_node);
}

bool Translator::visit(const IdentifierPath &_node) {
    return visitNode(_node);
}

bool Translator::visit(const IfStatement &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ImportDirective &_node) {
    return visitNode(_node);
}

bool Translator::visit(const IndexAccess &_node) {
    return visitNode(_node);
}

bool Translator::visit(const InheritanceSpecifier &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Literal &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Mapping &_node) {
    return visitNode(_node);
}

bool Translator::visit(const MemberAccess &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ModifierInvocation &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ParameterList &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Return &_node) {
    return visitNode(_node);
}

bool Translator::visit(const TupleExpression &_node) {
    return visitNode(_node);
}

bool Translator::visit(const UserDefinedTypeName &_node) {
    return visitNode(_node);
}

bool Translator::visit(const VariableDeclaration &_node) {
    return visitNode(_node);
}

bool Translator::visit(const VariableDeclarationStatement &_node) {
    return visitNode(_node);
}
