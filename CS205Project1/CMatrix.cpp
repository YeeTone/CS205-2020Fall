//
// Created by 16011 on 2020/10/27.
//
#pragma GCC optimize(3,"Ofast","inline")
#include "CMatrix.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <immintrin.h>
using namespace std;

bool CMatrix::isExpressedOmitted=true;

CMatrix::CMatrix(int r, int c) {
    this->row=r;
    this->column=c;
    delete [] data;
    data=new float[row*column]();
    std::fill(data,data+column*row,0);
    this->isZeroMatrix=true;
    this->isSquare=(r==c);
    if(isSquare){
        this->nonOneNumberMain=r;
        this->nonZeroNumber=0;
        this->nonZeroNumberNotMain=0;
        this->nonZeroNumberMain=0;
    }
}

float CMatrix::get(int r, int c) const {
    if(r>=this->row||c>=this->column){
        cerr<<"Matrix Index out of Bound!\n";
        return 0.0f;
    }else if(r<0||c<0){
        cerr<<"Negative Index!\n";
        return 0.0f;
    }else{
        return this->data[r*column+c];
    }
}

CMatrix CMatrix::singleMultiply(const CMatrix* cm) const {
    CMatrix output(this->row,cm->column);
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < cm->column; ++j) {
            double value=0;
            for (int k = 0; k < this->column; ++k) {
                if(get(i,k)!=0&&cm->get(k,j)!=0){
                    value+=get(i,k)*cm->get(k,j);
                }
            }
            output.set(i,j,(float)value+output.get(i,j));
        }
    }
    return output;
}

void CMatrix::set(int r, int c, float value){
    if(r>=this->row||c>=this->column){
        cerr<<"Matrix Index out of Bound2!\n";
        return;
    }else if(r<0||c<0){
        cerr<<"Negative Index!\n";
        return;
    }

    if(isSquare){
        if(r==c){
            if(value==1){
                nonOneNumberMain-=1;
            }else if(data[r*column+c]==1){
                nonOneNumberMain+=1;
            }
            if(value!=0){
                nonZeroNumberMain+=1;
            }else{
                nonZeroNumberMain-=1;
            }
        }else{
            if(value!=0){
                nonZeroNumberNotMain+=1;
            }else{
                nonZeroNumberNotMain-=1;
            }
        }
    }
    if(value!=0){
        nonZeroNumber+=1;
    }else{
        nonZeroNumber-=1;
    }
    this->data[r*column+c]=value;

    isZeroMatrix=(nonZeroNumber==0);
    isDiagonal=(isSquare&&nonZeroNumberNotMain==0);
    isIdentical=(isSquare&&isDiagonal&&nonOneNumberMain==0);
}

void CMatrix::printCM() const {
    if(CMatrix::isExpressedOmitted&&row>6&&column>6){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<get(i,j)<<" ";
            }
            cout<<"... ";
            for (int j = 0; j < 3; ++j) {
                cout<<get(i,column-3+j)<<" ";
            }
            cout<<"\n";
        }
        cout<<"...\n";
        for (int i = row-3; i < row; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<get(i,j)<<" ";
            }
            cout<<"... ";
            for (int j = 0; j < 3; ++j) {
                cout<<get(i,column-3+j)<<" ";
            }
            cout<<"\n";
        }
    }else if(CMatrix::isExpressedOmitted&&row>6){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < column; ++j) {
                cout<<get(i,j)<<" ";
            }
            cout<<"\n";
        }
        cout<<"...\n";
        for (int i = row-3; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                cout<<get(i,j)<<" ";
            }
            cout<<"\n";
        }
    }else if(CMatrix::isExpressedOmitted&&column>6){
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<get(i,j)<<" ";
            }
            cout<<"... ";
            for (int j = 0; j < 3; ++j) {
                cout<<get(i,column-3+j)<<" ";
            }
            cout<<"\n";
        }
    }else{
        for (int i = 0; i < this->row; ++i) {
            for (int j = 0; j < this->column; ++j) {
                cout<<get(i,j)<<" ";
            }
            cout<<"\n";
        }
    }

}

void CMatrix::fill(float value) {
    std::fill(data,data+column*row,value);
    if(isSquare){
        if(value==0){
            nonZeroNumber=0;
            nonZeroNumberNotMain=0;
            nonZeroNumberMain=0;
        }else{
            nonZeroNumber=row*column;
            nonZeroNumberMain=row;
            nonZeroNumberNotMain=row*(column-1);
        }
        if(value==1){
            nonOneNumberMain=0;
        }
    }
    if(value!=0&&!isSquare){
        nonZeroNumber=row*column;
    }
    isZeroMatrix=(nonZeroNumber==0);
    isDiagonal=(isSquare&&nonZeroNumberNotMain==0);
    isIdentical=(isSquare&&isDiagonal&&nonOneNumberMain==0);
}

CMatrix CMatrix::multipleMultiply(const CMatrix* cm) const{
    vector<thread>threadPool;
    threadPool.reserve(thread_number);
    unsigned int each=this->row/thread_number;
    unsigned int start=0,end=each;
    auto* results=new float[(this->row)*(cm->column)]();

    for (int i = 0; i < thread_number; ++i) {
        if(i==thread_number-1){
            end=this->row;
        }
        threadPool.emplace_back(subMultiply,this,cm,start,end,results);
        start=end;
        end+=each;
    }

    for (int i=0;i<thread_number; ++i){
        threadPool[i].join();
    }

    CMatrix output(this->row,cm->column);
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < cm->column; ++j) {
            output.set(i,j,results[i*cm->column+j]);
        }
    }
    return output;
}

void CMatrix::subMultiply(const CMatrix* cm1,const CMatrix* cm2,int start,int end,float* results) {
    int i, k, j;
    int x = cm2->column / 8* 8;
    if(x==cm2->column){
        x-=8;
    }

    __m256 value1,value2;
    __m256 beforeAdded,added,multiply;
    float cm_i_k;
    for (i = start; i < end; ++i) {
        for (k = 0; k < cm1->column; ++k) {
            cm_i_k = cm1->get(i, k);
            if (cm_i_k == 0) {
                continue;
            }

            value1[0]=cm_i_k;
            value1[1]=cm_i_k;
            value1[2]=cm_i_k;
            value1[3]=cm_i_k;
            value1[4]=cm_i_k;
            value1[5]=cm_i_k;
            value1[6]=cm_i_k;
            value1[7]=cm_i_k;
            for (j = 0; j + 8 < cm2->column; j+=8) {
                value2=_mm256_loadu_ps(&cm2->data[k*cm2->column+j]);
                multiply=_mm256_mul_ps(value1,value2);
                beforeAdded=_mm256_loadu_ps(results+i*cm2->column+j);
                added=_mm256_add_ps(beforeAdded,multiply);
                _mm256_storeu_ps(results+i*cm2->column+j,added);

                /*results[i*cm2->column+j]+=cm_i_k*cm2->get(k,j);
                results[i*cm2->column+j+1]+=cm_i_k*cm2->get(k,j+1);
                results[i*cm2->column+j+2]+=cm_i_k*cm2->get(k,j+2);
                results[i*cm2->column+j+3]+=cm_i_k*cm2->get(k,j+3);
                results[i*cm2->column+j+4]+=cm_i_k*cm2->get(k,j+4);
                results[i*cm2->column+j+5]+=cm_i_k*cm2->get(k,j+5);
                results[i*cm2->column+j+6]+=cm_i_k*cm2->get(k,j+6);
                results[i*cm2->column+j+7]+=cm_i_k*cm2->get(k,j+7);*/
            }
            for (j = x; j < cm2->column; j++) {
                results[i * cm2->column + j] += cm1->get(i, k) * cm2->get(k, j);
            }
        }
    }
}

CMatrix CMatrix::addMatrix(const CMatrix* cm) const {
    if(this->column!=cm->column||this->row!=cm->row){
        cerr<<"The matrix size is not matched!"<<endl;
        return CMatrix(0,0);
    }
    int total;
    total = this->column * this->row;
    vector<thread>threadPool;
    unsigned int each=total/thread_number;
    unsigned int start=0,end=each;
    for (int i = 0; i < thread_number; ++i) {
        if(i==thread_number-1){
            end=this->row*this->column;
        }
        threadPool.emplace_back(subAdd,this,cm,start,end);
        start=end;
        end+=each;
    }
    for (int i=0;i<thread_number; ++i){
        threadPool[i].join();
    }
    return *this;
}

void CMatrix::subAdd(const CMatrix *cm1, const CMatrix *cm2, int start, int end) {
    for (int i = start; i < end; ++i) {
        cm1->data[i]=cm1->data[i]+cm2->data[i];
    }
}

void CMatrix::inverseSign(){
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->column; ++j) {
            if(get(i,j)==0){
                continue;
            }
            set(i,j,get(i,j)*-1);
        }
    }
}

[[nodiscard]] CMatrix CMatrix::transport() const{
    CMatrix transported(this->column,this->row);
    for (int i = 0; i < this->column; ++i) {
        for (int j = 0; j < this->row; ++j) {
            transported.set(i,j,this->get(j,i));
        }
    }
    return transported;
}

CMatrix CMatrix::vectorMultiply(const CMatrix* vector1,const CMatrix* vector2) {
    int vectorSize=vector1->column;
    unsigned int each=vectorSize/thread_number;
    unsigned int start=0,end=each;
    vector<thread>threadPool;
    threadPool.reserve(thread_number);
    auto* vectorResults=new float[thread_number]();
    for (int i = 0; i < thread_number; ++i) {
        if(i==thread_number-1){
            end=vectorSize;
        }
        threadPool.emplace_back(subVectorMultiply,vector1,vector2,start,end,vectorResults,i);
        start=end;
        end+=each;
    }
    for (int i=0;i<thread_number; ++i){
        threadPool[i].join();
    }
    double r=0;
    for (int i = 0; i < thread_number; ++i) {
        r+=vectorResults[i];
    }
    CMatrix out(1,1);
    out.set(0,0,(float)r);
    return out;
}

void CMatrix::subVectorMultiply
(const CMatrix *cm1, const CMatrix *cm2, int start, int end, float *results,int i) {
    double re=0;
    for (int j = start; j < end; ++j) {
        if(cm1->data[j]==0||cm2->data[j]==0){
            continue;
        }
        re+=cm1->data[j]*cm2->data[j];
    }
    results[i]=(float)re;
}

void CMatrix::setDiagonal(float value){
    if(!isSquare){
        cerr<<"The matrix is not a square!\n";
        return;
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < row; ++j) {
            if(i!=j){
                set(i,j,0);
            }else{
                set(i,j,value);
            }
        }
    }
    this->nonZeroNumberMain=(value==0?0:1)*row;
    this->nonZeroNumber=(value==0?0:1)*row;
    this->nonZeroNumberNotMain=0;
    this->nonOneNumberMain=(value==1?0:1)*row;
    this->isDiagonal= true;
    this->isZeroMatrix=(value==0);
    this->isIdentical=(value==1);
}

CMatrix CMatrix::diagonalMatrixMultiplication(const CMatrix *cm1, const CMatrix *cm2) {
    if(cm1->isDiagonal&&cm2->isDiagonal){
        CMatrix out(cm1->row,cm1->row);
        for (int i = 0; i < cm1->row; ++i) {
            if(cm1->get(i,i)==0||cm2->get(i,i)==0){
                continue;
            }
            out.set(i,i,cm1->get(i,i)*cm2->get(i,i));
        }
        return out;
    }else if(cm1->isDiagonal){
        CMatrix out(cm1->row,cm2->column);
        for (int i = 0; i < cm1->row; ++i) {
            if(cm1->get(i,i)==0){
                continue;
            }
            for (int j = 0; j < cm2->column; ++j) {
                out.set(i,j,cm1->get(i,i)*cm2->get(i,j));
            }
        }
        return out;
    }else if(cm2->isDiagonal){
        CMatrix out(cm1->row,cm2->column);
        for (int i = 0; i < cm2->column; ++i) {
            if(cm2->get(i,i)==0){
                continue;
            }
            for (int j = 0; j < cm1->row; ++j) {
                out.set(j,i,cm1->get(j,i)*cm2->get(i,i));
            }
        }
        return out;
    } else{
        return CMatrix(0,0);
    }
}

CMatrix CMatrix::getIdentical(int x) {
    CMatrix identical(x,x);
    for (int i = 0; i < x; ++i) {
        identical.set(i,i,1);
    }
    identical.nonOneNumberMain=0;
    identical.nonZeroNumberNotMain=0;
    identical.nonZeroNumberMain=x;
    identical.nonZeroNumber=x;
    identical.isIdentical=true;
    identical.isDiagonal=true;
    identical.isSquare=true;
    identical.isZeroMatrix=false;
    return identical;
}
