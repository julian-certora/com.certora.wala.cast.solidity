//
//  translator.h
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//

#include "solidityBridge.h"
#include <jni.h>

#include "CAstWrapper.h"

using namespace solidity::frontend;

class Translator : public ASTConstVisitor {
private:
    JNIEnv *jniEnv;
    CAstWrapper cast;
    
public:
    Translator(JNIEnv *env, Exceptions& ex, jobject ast) : cast(env, ex, ast), jniEnv(env) { }
    
    virtual bool visitNode(ASTNode const&) override;

    virtual bool visit(const Assignment &_node) override;
    virtual bool visit(const BinaryOperation &_node) override;
    virtual bool visit(const Block &_node) override;
    virtual bool visit(const ContractDefinition &_node) override;
    virtual bool visit(const ElementaryTypeName &_node) override;
    virtual bool visit(const ElementaryTypeNameExpression &_node) override;
    virtual bool visit(const EmitStatement &_node) override;
    virtual bool visit(const EventDefinition &_node) override;
    virtual bool visit(const ExpressionStatement &_node) override;
    virtual bool visit(const FunctionCall &_node) override;
    virtual bool visit(const FunctionDefinition &_node) override;
    virtual bool visit(const Identifier &_node) override;
    virtual bool visit(const IdentifierPath &_node) override;
    virtual bool visit(const IfStatement &_node) override;
    virtual bool visit(const ImportDirective &_node) override;
    virtual bool visit(const IndexAccess &_node) override;
    virtual bool visit(const InheritanceSpecifier &_node) override;
    virtual bool visit(const Literal &_node) override;
    virtual bool visit(const Mapping &_node) override;
    virtual bool visit(const MemberAccess &_node) override;
    virtual bool visit(const ModifierInvocation &_node) override;
    virtual bool visit(const ParameterList &_node) override;
    virtual bool visit(const Return &_node) override;
    virtual bool visit(const SourceUnit &_node) override;
    virtual bool visit(const TupleExpression &_node) override;
    virtual bool visit(const UserDefinedTypeName &_node) override;
    virtual bool visit(const VariableDeclaration &_node) override;
    virtual bool visit(const VariableDeclarationStatement &_node) override;

};
