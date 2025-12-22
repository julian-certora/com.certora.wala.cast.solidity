//
//  translator.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//
#include "translator.h"
#include "CAstWrapper.h"


bool Translator::visitNode(ASTNode const&_node) {
    indent();
    level++;
    std::cout << _node.location() << " " << _node.id() << " " << typeid(_node).name() << std::endl;
    jobject nothing = cast.makeNode(cast.EMPTY);
    ret(nothing);
    return true;
}

void Translator::endVisitNode(ASTNode const&_node) {
    level--;
}

bool Translator::visit(const SourceUnit &_node) {
    level = 0;
    visitNode(_node);
    std::vector<ASTPointer<ASTNode>> nodes = _node.nodes();
    size_t len = nodes.size();
    jobject children[ len ];
    int i = 0;
    for (std::vector<ASTPointer<ASTNode>>::iterator t=nodes.begin();
         t != nodes.end();
         ++t)
    {
        t->get()->accept(*this);
        children[i++] = last();
    }
    return false;
}

class ContractContext : public Context {
private:
    std::vector<jobject> supers;
    
public:
    ContractContext(Context *parent) : Context(parent) {
        
    }
    
    virtual void addSuperclass(std::string name) override {
        supers.push_back(types[name]);
    }
    
    virtual std::vector<jobject> superClasses() {
        return supers;
    }
};

bool Translator::visit(const ContractDefinition &_node) {
    visitNode(_node);
    context = new ContractContext(context);
    jobject n = cast.makeConstant( _node.name().c_str() );
    return true;
}

void Translator::endVisit(const ContractDefinition &_node) {
    std::vector<jobject> supers = context->superClasses();
    jclass sCls = jniEnv->FindClass("java/util/HashSet");
    jmethodID sCtor = jniEnv->GetMethodID(sCls, "<init>", "()V");
    jmethodID add = jniEnv->GetMethodID(sCls, "add", "(Ljava/lang/Object;)Z");
    jobject supersSet = jniEnv->NewObject(sCls, sCtor);
    for (std::vector<jobject>::iterator t=supers.begin();
         t != supers.end();
         ++t) {
        jniEnv->CallBooleanMethod(supersSet, add, *t);
    }
    jclass cCls = jniEnv->FindClass("com/certora/wala/cast/solidity/types/ContractType");
    jmethodID cCtor = jniEnv->GetMethodID(cCls, "<init>", "(Ljava/lang/String;Ljava/util/Set;)V");
    jobject type = jniEnv->NewObject(cCls, cCtor, jniEnv->NewStringUTF(_node.name().c_str()), supersSet);

    jclass obj = jniEnv->FindClass("java/lang/Object");
    jmethodID toString = jniEnv->GetMethodID(obj, "toString", "()Ljava/lang/String;");
    indent();
    std::cout
        << "contract "
        << jniEnv->GetStringUTFChars((jstring)jniEnv->CallObjectMethod(type, toString), 0)
        << std::endl;

    types[_node.name()] = type;
    
    context = context->parent();
    
    endVisitNode(_node);
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
    std::string typeName = "";
    const std::vector<ASTString> names = _node.name().path();
    for (std::vector<ASTString>::const_iterator t = names.begin();
         t != names.end();
         ++t)
    {
        typeName += t->data();
    }

    context->addSuperclass(typeName);
    
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
