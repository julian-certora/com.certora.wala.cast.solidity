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

std::map<std::string, jobject> types;

class Context {
private:
    Context *_parent;
    
protected:
    Context(Context *parent) : _parent(parent) { }
    
public:
    Context *parent() { return _parent; }
    virtual void addSuperclass(std::string superType) = 0;
    virtual std::vector<jobject> superClasses() = 0;
};

class Translator : public ASTConstVisitor {
private:
    JNIEnv *jniEnv;
    CAstWrapper cast;
    
    Context *context = NULL;
    
    jobject tree;
    
    void ret(jobject v) {
        tree = v;
    }
    
    jobject last() {
        return tree;
    }
    
    int level;
    
    void indent() {
        for(int i = 0; i < level; i++) {
            std::cout << " ";
        }
    }
    
    jobject print(jobject v) {
        jclass obj = jniEnv->FindClass("java/lang/Object");
        jmethodID toString = jniEnv->GetMethodID(obj, "toString", "()Ljava/lang/String;");
        std::cout << jniEnv->GetStringUTFChars((jstring)jniEnv->CallObjectMethod(v, toString), 0);
        return v;
    }
    
public:
    Translator(JNIEnv *env, Exceptions& ex, jobject ast) : cast(env, ex, ast), jniEnv(env) {
        level = 0;
    }
    
    virtual bool visitNode(ASTNode const&) override;
    virtual void endVisitNode(ASTNode const&_node) override;

    virtual bool visit(const Assignment &_node) override;
    virtual bool visit(const BinaryOperation &_node) override;
    virtual bool visit(const Block &_node) override;
    virtual bool visit(const ContractDefinition &_node) override;
    virtual void endVisit(const ContractDefinition &_node) override;
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
