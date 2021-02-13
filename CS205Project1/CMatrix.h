//
// Created by 16011 on 2020/10/27.
//
#pragma GCC optimize(3,"Ofast","inline")

#include <thread>

#ifndef PROJECT1_CMATRIX_H
#define PROJECT1_CMATRIX_H

#define thread_number thread::hardware_concurrency()
#include <iostream>

using namespace std;
class CMatrix {
private:
    bool isSquare= false;
    bool isDiagonal= false;
    bool isIdentical=false;
    bool isZeroMatrix= false;
    int nonZeroNumberNotMain=0;
    int nonZeroNumberMain=0;
    int nonOneNumberMain=0;
    int nonZeroNumber=0;
private:
    int row=0;
    int column=0;
    float* data= nullptr;
public:
    static bool isExpressedOmitted;
    explicit CMatrix(int r,int c);
    [[nodiscard]] float get(int r,int c) const;
    void set(int r,int c,float value);
    void printCM() const;
    void fill(float value);
    void inverseSign();
    void setDiagonal(float value);
    [[nodiscard]] CMatrix transport()const;
    static CMatrix getIdentical(int x);
    static inline CMatrix getZeros(int r,int c){
        return CMatrix(r,c);
    }
    inline CMatrix operator*(const CMatrix& cm)const{
        if(!check2MatrixMultiplyMatch(this,&cm)){
            cerr<<"These 2 Matrix Size is not Matched! No multiplication is allowed!\n";
            return CMatrix(0,0);
        }
        if(this->isZeroMatrix||cm.isZeroMatrix){
            return zeroMatrixMultiplication(this,&cm);
        }else if(this->isIdentical||cm.isIdentical){
            return identicalMatrixMultiplication(this,&cm);
        }else if(this->isDiagonal||cm.isDiagonal){
            return diagonalMatrixMultiplication(this,&cm);
        }else if(this->row==1){
            return vectorMultiply(this,&cm);
        }else if(this->row<=thread_number){
            return singleMultiply(&cm);
        }else{
            return multipleMultiply(&cm);
        }
    };
    inline CMatrix operator+(const CMatrix& cm)const{
        return addMatrix(&cm);
    };
    inline CMatrix operator-(CMatrix& cm)const{
        cm.inverseSign();
        CMatrix out = *this+cm;
        cm.inverseSign();
        return out;
    };
    inline CMatrix operator^(int x){
        //quick power
        if(!isSquare){
            cerr<<"This is not a square! No power can be calculated!\n";
            return CMatrix(0,0);
        }
        if(x<0){
            cerr<<"The pow number must be natural number!\n";
            return CMatrix(0,0);
        }
        CMatrix cm=getIdentical(this->row);
        while(x!=0){
            if((x&1)==1){
                cm=cm*(*this);
            }
            *this=(*this)*(*this);
            x>>=1;
        }
        return cm;
    }
    inline bool operator==(const CMatrix& cm)const{
        if(this->row!=cm.row||this->column!=cm.column){
            return false;
        }
        for (long i = 0; i < this->row*this->column; ++i) {
            if(this->data[i]!=cm.data[i]){
                return false;
            }
        }
        return true;
    }

private:
    static void subMultiply(const CMatrix* cm1,const CMatrix* cm2,int start,int end,float* results);
    static void subAdd(const CMatrix* cm1,const CMatrix* cm2,int start,int end);
    static CMatrix vectorMultiply(const CMatrix* vector1,const CMatrix* vector2);
    static void subVectorMultiply(const CMatrix* cm1,const CMatrix* cm2,int start,int end,float* results,int i);
    static inline bool check2MatrixMultiplyMatch(const CMatrix* cm1,const CMatrix* cm2){
        return (cm1->column==cm2->row);
    }
    static inline CMatrix zeroMatrixMultiplication(const CMatrix* cm1,const CMatrix* cm2){
        return CMatrix(cm1->row,cm2->column);
    }
    static CMatrix diagonalMatrixMultiplication(const CMatrix* cm1,const CMatrix* cm2);
    static CMatrix identicalMatrixMultiplication(const CMatrix* cm1,const CMatrix* cm2){
        if(cm1->isIdentical){
            return *cm2;
        }else if(cm2->isIdentical){
            return *cm1;
        }
        return CMatrix(0,0);
    }
    CMatrix singleMultiply(const CMatrix* cm) const;
    CMatrix multipleMultiply(const CMatrix* cm) const;
    CMatrix addMatrix(const CMatrix* cm) const;

};



#endif //PROJECT1_CMATRIX_H

