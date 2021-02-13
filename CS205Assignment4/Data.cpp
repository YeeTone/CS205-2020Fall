//
// Created by 16011 on 2020/11/24.
//

#include "Data.h"

Data::Data(long size) {
    this->values=new float[size]();
    this->referenceTimes=1;
}

Data::~Data() {
    delete values;
}

float* Data::get_values_ptr() {
    return values;
}

int Data::getReference() const {
    return this->referenceTimes;
}

void Data::addReference() {
    this->referenceTimes+=1;
}

void Data::removeReference() {
    this->referenceTimes-=1;
}

void Data::setDefaultRef() {
    this->referenceTimes=1;
}





