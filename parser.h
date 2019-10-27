#ifndef DESKCALCULATOR_PARSER_H
#define DESKCALCULATOR_PARSER_H
#include <iostream>
#include <sstream>
#include <iostream>
#include <sstream>
#include <map>
#include "error.h"

using std::string; using std::istream; using std::cerr; using std::map; using std::cin; using std::cout;

enum class Kind : char{
    name, number, end,
    plus='+', minus='-', mul='*', div='/', print=';', assign='=', lp='(', rp=')'
};
struct Token {
    Kind kind;
    string string_value;
    double number_value;
};

class Token_stream {
public:
    explicit Token_stream(istream& s) : ip{&s},owns(false), ct{Kind::end}{}
    explicit Token_stream(istream* p) : ip{p},owns(true), ct{Kind::end}{}
    ~Token_stream(){close();}

    Token get(){
        char ch;
        do{
            if(!ip->get(ch)) return ct={Kind::end};
        } while(ch!='\n' && isspace(ch));

        switch(ch){
            case ';':
            case '\n':
                return ct={Kind::print};
            case '*':
            case '/':
            case '+':
            case '-':
            case '(':
            case ')':
            case '=':
                return ct={static_cast<Kind>(ch)};
            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            case '.':
                ip->putback(ch);
                *ip >> ct.number_value;
                ct.kind=Kind::number;
                return ct;
            default:
                if(isalpha(ch)){
                    ct.string_value = ch;
                    while(ip->get(ch)){
                        if(isalnum(ch))
                            ct.string_value += ch;
                        else{
                            ip->putback(ch);
                            break;
                        }
                    }
                    ct.kind = Kind::name;
                    return ct;
                }
                error("bad token");
                return ct={Kind::print};
        }
    }

    Token & current(){
        return ct;
    }

    void set_input(istream& s) {close(); ip=&s; owns=false;}
    void set_input(istream* p) {close(); ip=p; owns=true;}
private:
    void close() {if (owns) delete ip;}

    istream* ip;
    bool owns;
    Token ct{Kind::end};
};

extern Token_stream ts;

#endif //DESKCALCULATOR_PARSER_H
