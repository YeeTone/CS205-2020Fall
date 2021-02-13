#ifndef ASSIGNMENT4_CMATRIX_H
#define ASSIGNMENT4_CMATRIX_H

#include <iostream>
#include "Data.h"
using namespace std;

class CMatrix {
private:
    //Requirement1:
    int row=0;//the Row number
    int column=0;//the Column number
    Data* dataptr= nullptr;//the float elements pointer
private:
    static int count;
    int matrix_id;
public:
    static bool isExpressOmitted;
    //Requirement2: constructor
    explicit CMatrix(int r=0, int c=0);
    explicit CMatrix(int r,int c,const float* outData);
    CMatrix(const CMatrix& cm);
    //Requirement2: destructor
    ~CMatrix();

    //Requirement2: operator << and =
    friend ostream& operator<<(ostream& os,const CMatrix& cm);

    CMatrix operator+(const CMatrix& cm) const;
    CMatrix operator-(const CMatrix& cm) const;
    CMatrix operator*(const CMatrix& cm) const;
    CMatrix& operator=(const CMatrix& cm);
    friend CMatrix operator*(const CMatrix& cm,int x);
    friend CMatrix operator*(int x,const CMatrix& cm);
    CMatrix operator^(int x) const;

    friend bool operator==(const CMatrix& cm1,const CMatrix& cm2);
    friend bool operator!=(const CMatrix& cm1,const CMatrix& cm2);
    void operator+=(const CMatrix& cm);
    void operator-=(const CMatrix& cm);
    void operator*=(const CMatrix& cm);
    void operator*=(int x);
    const float* operator[](int i);
    //Additional Method:
    [[nodiscard]] float get(int r,int c) const;
    void set(int r,int c,float v);
    [[nodiscard]] int getRow() const;
    [[nodiscard]] int getColumn() const;
    [[nodiscard]] int getRef()const;
    [[nodiscard]] CMatrix clone()const;
    void copyOf(const CMatrix& cm);
private:
    [[nodiscard]] bool rangeCheck(int r,int c) const;
    void data_gc();
    void setIdentity();

};


#endif //ASSIGNMENT4_CMATRIX_H
