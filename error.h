#ifndef DESKCALCULATOR_ERROR_H
#define DESKCALCULATOR_ERROR_H
#include <iostream>
#include <sstream>

using std::string; using std::cerr;
extern int no_of_errors;
double error(const string& s){
    no_of_errors++;
    cerr << "error:" << s << '\n';
    return 1;
}


#endif //DESKCALCULATOR_ERROR_H
