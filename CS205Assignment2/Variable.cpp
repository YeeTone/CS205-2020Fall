//
// Created by 16011 on 2020/9/24.
//

#include "Variable.h"
#include <iostream>

Variable::Variable() {

}
Variable::Variable(std::string vn, CWTNumber vv) {
    this->varName=vn;
    this->varValue=vv;
}
std::string Variable::getVarName() {
    return this->varName;
}
CWTNumber Variable::getVarValue() {
    return this->varValue;
}
void Variable ::setVarValue(CWTNumber cn) {
    this->varValue=cn;
}
