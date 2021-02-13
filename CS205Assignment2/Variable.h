//
// Created by 16011 on 2020/9/24.
//

#ifndef CPPLEARN_VARIABLE_H
#define CPPLEARN_VARIABLE_H

#include <iostream>
#include "CWTNumber.h"

class Variable {
private:
    CWTNumber varValue;
    std::string varName;
public:
    Variable();
    Variable(std::string vn,CWTNumber vv);
    CWTNumber getVarValue();
    std::string getVarName();
    void setVarValue(CWTNumber cn);
};


#endif //CPPLEARN_VARIABLE_H
