#ifndef CALC_ALGORITHM_H
#define CALC_ALGORITHM_H

#include <sstream>
#include <unordered_map>
#include <string>

namespace cstm
{
    bool isdouble(std::string myString);


    struct Op;


    float rec(std::string s);

    double calcExpr(std::string s);
}


#endif // CALC_ALGORITHM_H
