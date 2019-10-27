#include "dc.h"
#include <sstream>
#include <iostream>

using namespace Lexer;
using std::string; using std::cout; using std::cin;


void Driver::calculate() {
    for (;;) {
        ts.get();
        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print)continue;
        cout << Parser::expr(false) << '\n';
    }
}

int main(int argc, char* argv[]){
    Table::table["pi"]=3.14159265;
    Table::table["e"]=2.718281828;
    Driver::calculate();
    return Error::no_of_errors;
}
