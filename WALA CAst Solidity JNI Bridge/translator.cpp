//
//  translator.cpp
//  WALA CAst Solidity
//
//  Created by Julian Dolby on 12/19/25.
//
#include "translator.h"
#include "CAstWrapper.h"

std::map<std::string, jobject> types;

bool Translator::visitNode(ASTNode const&_node) {
    level++;
    indent();
    std::cout << _node.location() << " " << _node.id() << " " << typeid(_node).name() << std::endl;
    jobject nothing = cast.makeNode(cast.EMPTY);
    ret(nothing);
    return true;
}

void Translator::endVisitNode(ASTNode const&_node) {
    level--;
}

bool Translator::visit(const SourceUnit &_node) {
    visitNode(_node);
    std::vector<ASTPointer<ASTNode>> nodes = _node.nodes();
    int len = (int)nodes.size();
    jclass cnc = jniEnv->FindClass("com/ibm/wala/cast/tree/CAstNode");
    jobjectArray children = jniEnv->NewObjectArray(len, cnc, NULL);

    int i = 0;
    for (std::vector<ASTPointer<ASTNode>>::iterator t=nodes.begin();
         t != nodes.end();
         ++t, i++)
    {
        t->get()->accept(*this);
        jniEnv->SetObjectArrayElement(children, i, last());
    }
    
    ret(cast.makeNode(cast.BLOCK_STMT, children));
    return false;
}

class ContractContext : public virtual VariableContainerContext, public virtual FunctionContainerContext, public virtual DelegatingContext {
private:
    std::vector<jobject> supers;
    
public:
    ContractContext(DelegatingContext *parent) : DelegatingContext(parent), FunctionContainerContext(parent), VariableContainerContext(parent){
        
    }
    
    virtual void addSuperclass(std::string name) override {
        supers.push_back(types[name]);
    }
    
    virtual std::vector<jobject>& superClasses() override {
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
    std::vector<jobject>& supers = context->superClasses();
    jclass sCls = jniEnv->FindClass("java/util/HashSet");
    jmethodID sCtor = jniEnv->GetMethodID(sCls, "<init>", "()V");
    jmethodID add = jniEnv->GetMethodID(sCls, "add", "(Ljava/lang/Object;)Z");
    jobject supersSet = jniEnv->NewObject(sCls, sCtor);
    for (std::vector<jobject>::iterator t=supers.begin();
         t != supers.end();
         ++t) {
        jniEnv->CallBooleanMethod(supersSet, add, *t);
    }
    jclass ctCls = jniEnv->FindClass("com/certora/wala/cast/solidity/loader/ContractType");
    jmethodID ctCtor = jniEnv->GetMethodID(ctCls, "<init>", "(Ljava/lang/String;Ljava/util/Set;)V");
    jstring entityName = jniEnv->NewStringUTF(_node.name().c_str());
    jobject type = jniEnv->NewObject(ctCls, ctCtor, entityName, supersSet);

    indent();
    std::cout << "contract ";
    print(type);
    std::cout << std::endl;

    types[_node.name()] = type;
    
    jobject entitiesSet = jniEnv->NewObject(sCls, sCtor);
    std::map<jstring, jobject>& functions = context->functions();
    for (std::map<jstring,jobject>::iterator t=functions.begin();
         t != functions.end();
         ++t) {
        jniEnv->CallBooleanMethod(entitiesSet, add, t->second);
    }

    jclass ceCls = jniEnv->FindClass("com/certora/wala/cast/solidity/tree/ContractEntity");
    jmethodID ceCtor = jniEnv->GetMethodID(ceCls, "<init>", "(Ljava/lang/String;Lcom/ibm/wala/cast/tree/CAstType;Lcom/ibm/wala/cast/tree/CAstSourcePositionMap$Position;Lcom/ibm/wala/cast/tree/CAstSourcePositionMap$Position;Ljava/util/Set;)V");
    jniEnv->NewObject(ceCls, ceCtor, entityName, makePosition(_node.location()), makePosition(_node.nameLocation()));
    
    context = context->parent();
    
    endVisitNode(_node);
}

bool Translator::visit(const Assignment &_node) {
    _node.leftHandSide().accept(*this);
    jobject lhs = last();

    _node.rightHandSide().accept(*this);
    jobject rhs = last();

    ret(print(record(cast.makeNode(cast.ASSIGN, lhs, rhs), _node.location())));
    return false;
}

jobject translateOpcode(CAstWrapper& cast, Token t) {
    switch(t) {
        case Token::Add: return cast.OP_ADD;
        case Token::Sub: return cast.OP_SUB;
        case Token::Mul: return cast.OP_MUL;
        case Token::Div: return cast.OP_DIV;
        case Token::Equal: return cast.OP_EQ;
        case Token::NotEqual: return cast.OP_NE;
        case Token::LessThan: return cast.OP_LT;
        case Token::LessThanOrEqual: return cast.OP_LE;
        case Token::GreaterThan: return cast.OP_GT;
        case Token::GreaterThanOrEqual: return cast.OP_GE;
        default: return NULL;
    }
 }

bool Translator::visit(const BinaryOperation &_node) {
    _node.leftExpression().accept(*this);
    jobject left = last();

    _node.rightExpression().accept(*this);
    jobject right = last();

    jobject op = translateOpcode(cast, _node.getOperator());
    
    jobject expr = cast.makeNode(cast.BINARY_EXPR, op, left, right);
    ret(record(expr, _node.location()));
    
    indent();
    std::cout << "expr: ";
    print(expr);

    return false;
}

bool Translator::visit(const Block &_node) {
    const std::vector<ASTPointer<Statement>> nodes = _node.statements();
    int len = (int)nodes.size();
    jclass cnc = jniEnv->FindClass("com/ibm/wala/cast/tree/CAstNode");
    jobjectArray children = jniEnv->NewObjectArray(len, cnc, NULL);

    int i = 0;
    for (std::vector<ASTPointer<Statement>>::const_iterator t=nodes.begin();
         t != nodes.end();
         ++t, i++)
    {
        t->get()->accept(*this);
        jniEnv->SetObjectArrayElement(children, i, last());
    }
    
    ret(record(print(cast.makeNode(cast.BLOCK_STMT, children)), _node.location()));
    return false;
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
    _node.expression().accept(*this);
    jobject expr = last();
    
    ret(record(print(cast.makeNode(cast.EXPR_STMT, expr)), _node.location()));
    
    return false;
}

bool Translator::visit(const FunctionCall &_node) {
    _node.expression().accept(*this);
    jobject fun = last();
    
    int i = 0;
    std::vector<ASTPointer<const Expression>> args = _node.arguments();
    int len = (int)args.size();
    jclass cnc = jniEnv->FindClass("com/ibm/wala/cast/tree/CAstNode");
    jobjectArray children = jniEnv->NewObjectArray(len, cnc, NULL);
   for (std::vector<ASTPointer<const Expression>>::const_iterator t=args.begin();
         t != args.end();
         ++t, i++)
    {
        t->get()->accept(*this);
        jniEnv->SetObjectArrayElement(children, i, last());
    }

    ret(record(print(cast.makeNode(cast.CALL, fun, children)), _node.location()));
    return false;
}

bool Translator::visit(const FunctionDefinition &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Identifier &_node) {
    std::cout << _node.name() << " " << _node.location();
    ret(record(cast.makeNode(cast.VAR, cast.makeConstant(_node.name().c_str())), _node.location()));
    return false;
}

bool Translator::visit(const IdentifierPath &_node) {
    return visitNode(_node);
}

bool Translator::visit(const IfStatement &_node) {
    _node.condition().accept(*this);
    jobject cond = last();
    
    _node.trueStatement().accept(*this);
    jobject then = last();

    if (_node.falseStatement() != NULL) {
        _node.falseStatement()->accept(*this);
        jobject otherwise = last();
        
        ret(record(print(cast.makeNode(cast.IF_STMT, cond, then, otherwise)), _node.location()));
    } else {
        ret(record(print(cast.makeNode(cast.IF_STMT, cond, then)), _node.location()));
    }
    
    return false;
}

bool Translator::visit(const ImportDirective &_node) {
    return visitNode(_node);
}

bool Translator::visit(const IndexAccess &_node) {
    _node.baseExpression().accept(*this);
    jobject obj = last();
    
    _node.indexExpression()->accept(*this);
    jobject idx = last();

    jobject ref = cast.makeNode(cast.ARRAY_REF, obj, idx);
    
    ret(record(ref, _node.location()));
    return false;
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
    Type const* type = _node.annotation().type;
    switch (type->category())
    {
        case Type::Category::RationalNumber:
        case Type::Category::Bool:
        case Type::Category::Address:
            ret(cast.makeConstant((long)type->literalValue(&_node)));
            break;
        case Type::Category::StringLiteral:
            ret(cast.makeConstant(_node.value().c_str()));
            break;
        default:
            ret(cast.makeNode(cast.EMPTY));
    }
    return false;
}

bool Translator::visit(const Mapping &_node) {
    return visitNode(_node);
}

bool Translator::visit(const MemberAccess &_node) {
    _node.expression().accept(*this);
    jobject obj = last();
    
    jobject var = cast.makeConstant( _node.memberName().c_str() );
    
    jobject ref = cast.makeNode(cast.OBJECT_REF, obj, var);
    
    ret(record(ref, _node.location()));
    return false;
}

bool Translator::visit(const ModifierInvocation &_node) {
    return visitNode(_node);
}

bool Translator::visit(const ParameterList &_node) {
    return visitNode(_node);
}

bool Translator::visit(const Return &_node) {
    if (_node.expression() != NULL) {
        _node.expression()->accept(*this);
        jobject val = last();
        ret(record(print(cast.makeNode(cast.RETURN, val)), _node.location()));
    } else {
        ret(record(print(cast.makeNode(cast.RETURN)), _node.location()));
    }
    return false;
}

bool Translator::visit(const TupleExpression &_node) {
    if (_node.components().size() == 1) {
        _node.components().at(0)->accept(*this);
        return false;
    } else {
        return visitNode(_node);
    }
}

bool Translator::visit(const UserDefinedTypeName &_node) {
    return visitNode(_node);
}

bool Translator::visit(const VariableDeclaration &_node) {
    jclass sct = jniEnv->FindClass("com/certora/wala/cast/solidity/tree/SolidityCAstType");
    jmethodID gt = jniEnv->GetStaticMethodID(sct, "get", "(Ljava/lang/String;)Lcom/ibm/wala/cast/tree/CAstType;");
    string tn = _node.type()->identifier();
    std::cout << sct << " " << gt << " " << tn << std::endl;
    jobject jtn = jniEnv->NewStringUTF(tn.c_str());
    
    jobject type = jniEnv->CallStaticObjectMethod(sct, gt, jtn);
    
    return visitNode(_node);
}

bool Translator::visit(const VariableDeclarationStatement &_node) {
    return visitNode(_node);
}
