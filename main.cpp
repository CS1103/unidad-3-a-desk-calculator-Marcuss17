#include "parser.h"

int no_of_errors;
map<string,double> table;
Token_stream ts{cin};

void calculate(){
    for (;;) {
        ts.get();
        if (ts.current().kind == Kind::end) break;
        if (ts.current().kind == Kind::print)continue;
        cout << expr(false) << '\n';
    }
};

int main(int argc, char* argv[]){
    table["pi"]=3.14159265;
    table["e"]=2.718281828;
    calculate();
    return no_of_errors;
}





