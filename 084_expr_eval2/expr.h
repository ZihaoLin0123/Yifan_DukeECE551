#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <sstream>
class Expression{
public:
     virtual std::string toString() const = 0; 
     virtual ~Expression(){}
};

class NumExpression : public Expression{
protected:
    long numExpr;
public:
    NumExpression(long num):numExpr(num){}

    virtual std::string toString() const{
        std::stringstream ss;
        ss << numExpr;
        return ss.str();
    }

    virtual ~NumExpression(){}
};

class PlusExpression : public Expression{
protected:
    Expression *l;
    Expression *r;
public:
    PlusExpression(Expression * lhs, Expression * rhs): l(lhs), r(rhs){}
    virtual std::string toString() const{
        std::stringstream ss;
        ss << "(" << l->toString() << "+" << r->toString() << ")";
        return ss.str();
    }
    virtual  ~PlusExpression(){
        delete l;
        delete r;
    }
};

class MinusExpression : public Expression{
protected:
    Expression *l;
    Expression *r;
public:
    MinusExpression(Expression * lhs, Expression * rhs): l(lhs), r(rhs){}
    virtual std::string toString() const{
        std::stringstream ss;
        ss << "(" << l->toString() << "-" << r->toString() << ")";
        return ss.str();
    }
    virtual  ~MinusExpression(){
        delete l;
        delete r;
    }
};


class TimesExpression : public Expression{
protected:
    Expression *l;
    Expression *r;
public:
    TimesExpression(Expression * lhs, Expression * rhs): l(lhs), r(rhs){}
    virtual std::string toString() const{
        std::stringstream ss;
        ss << "(" << l->toString() << "*" << r->toString() << ")";
        return ss.str();
    }
    virtual  ~TimesExpression(){
        delete l;
        delete r;
    }
};

class DivExpression : public Expression{
protected:
    Expression *l;
    Expression *r;
public:
    DivExpression(Expression * lhs, Expression * rhs): l(lhs), r(rhs){}
    virtual std::string toString() const{
        std::stringstream ss;
        ss << "(" << l->toString() << "-" << r->toString() << ")";
        return ss.str();
    }
    virtual  ~DivExpression(){
        delete l;
        delete r;
    }
};


