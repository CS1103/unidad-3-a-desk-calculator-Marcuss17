#ifndef DESKCALCULATOR_PARSER_H
#define DESKCALCULATOR_PARSER_H
#include "lexer.h"

extern map<string,double> table;
double term(bool);
double expr(bool get){
    double left = term(get);

    for(;;){
        switch(ts.current().kind){
            case Kind::plus:
                left += term(true);
                break;
            case Kind::minus:
                left -= term(true);
                break;
            default:
                return left;
        }
    }
}
double prim(bool get){
    if(get) ts.get();

    switch(ts.current().kind){
        case Kind::number:
        {
            double v = ts.current().number_value;
            ts.get();
            return v;
        }
        case Kind::name:
        {
            double& v = table[ts.current().string_value];
            if(ts.get().kind == Kind::assign) v = expr(true);
            return v;
        }
        case Kind::minus:
            return -prim(true);
        case Kind::lp:
        {
            auto e = expr(true);
            if(ts.current().kind != Kind::rp) return error("')' expectend");
            ts.get();
            return e;
        }
        default:
            return error("primary expected");
    }
}
double term(bool get){
    double left = prim(get);

    for(;;){
        switch (ts.current().kind){
            case Kind::mul:
                left *= prim(true);
                break;
            case Kind::div:
                if(auto d = prim(true)){
                    left /= d;
                    break;
                }
                return error("divide by 0");
            default:
                return left;
        }
    }
}


#endif //DESKCALCULATOR_PARSER_H
