//
// Created by 16011 on 2020/11/23.
//

#include "CMatrix.h"
#include <cstring>
#include <iostream>
using namespace std;

bool CMatrix::isExpressOmitted=true;
int CMatrix::count=0;
//Requirement2:
CMatrix::CMatrix(int r, int c) {
    this->row=r;
    this->column=c;
    data_gc();
    this->dataptr=new Data(r*c);
    count++;
    matrix_id=count;
    cout<<"CMatrix"<<count<<" is created!"<<endl;
}
CMatrix::CMatrix(int r, int c, const float* outData) {
    this->row=r;
    this->column=c;
    data_gc();
    this->dataptr=new Data(r*c);
    memcpy(this->dataptr->get_values_ptr(),outData,((long)sizeof(float))*r*c);
    count++;
    matrix_id=count;
    cout<<"CMatrix"<<count<<" is created!"<<endl;
}
CMatrix::CMatrix(const CMatrix &cm) {
    if(this==(&cm)){
        return;
    }
    this->row=cm.row;
    this->column=cm.column;
    data_gc();
    this->dataptr=cm.dataptr;
    this->dataptr->addReference();
    count++;
    matrix_id=count;
    cout<<"CMatrix"<<count<<" is created!"<<endl;
}
CMatrix::~CMatrix() {
    cout << "CMatrix"<<matrix_id<<" is deleted!" << endl;
    count--;
    data_gc();
}
ostream& operator<<(ostream& os, const CMatrix& cm){
    int row=cm.getRow();
    int column=cm.getColumn();
    cout<<"Row: "<<row<<", Column:"<<column<<endl;
    if(CMatrix::isExpressOmitted&&row>6&&column>6){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<cm.get(i,j)<<" ";
            }
            cout<<"... ";
            for (int j = 0; j < 3; ++j) {
                cout<<cm.get(i,column-3+j)<<" ";
            }
            cout<<"\n";
        }
        cout<<"...\n";
        for (int i = row-3; i < row; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<cm.get(i,j)<<" ";
            }
            cout<<"... ";
            for (int j = 0; j < 3; ++j) {
                cout<<cm.get(i,column-3+j)<<" ";
            }
            cout<<"\n";
        }
    }else if(CMatrix::isExpressOmitted&&row>6){
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < column; ++j) {
                cout<<cm.get(i,j)<<" ";
            }
            cout<<"\n";
        }
        cout<<"...\n";
        for (int i = row-3; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                cout<<cm.get(i,j)<<" ";
            }
            cout<<"\n";
        }
    }else if(CMatrix::isExpressOmitted&&column>6){
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout<<cm.get(i,j)<<" ";
            }
            cout<<"... ";
            for (int j = 0; j < 3; ++j) {
                cout<<cm.get(i,column-3+j)<<" ";
            }
            cout<<"\n";
        }
    }else{
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                cout<<cm.get(i,j)<<" ";
            }
            cout<<"\n";
        }
    }
    return os;
}
CMatrix CMatrix::operator+(const CMatrix& cm) const{
    if(this->row!=cm.row||this->column!=cm.column){
        cerr<<"The matrix size is not matched! No calculation is allowed!";
        return CMatrix(0,0);
    }
    CMatrix output(this->row,this->column);
    for (int i = 0; i < this->row*this->column; ++i) {

        output.dataptr->get_values_ptr()[i]=cm.dataptr->get_values_ptr()[i]+this->dataptr->get_values_ptr()[i];
    }
    output.dataptr->setDefaultRef();
    return output;
}
CMatrix CMatrix::operator-(const CMatrix& cm) const{
    if(this->row!=cm.row||this->column!=cm.column){
        cerr<<"The matrix size is not matched! No minus is allowed!";
        return CMatrix(0,0);
    }
    CMatrix output(this->row,this->column);
    for (int i = 0; i < this->row*this->column; ++i) {
        output.dataptr->get_values_ptr()[i]=cm.dataptr->get_values_ptr()[i]+this->dataptr->get_values_ptr()[i];
    }
    output.dataptr->setDefaultRef();
    return output;
}
CMatrix CMatrix::operator*(const CMatrix& cm) const {
    if(this->column!=cm.row){
        cerr<<"The matrix size is not matched! No multiplication is allowed!"<<endl;
        return CMatrix(0,0);
    }
    CMatrix output(this->row,cm.column);
    double this_i_j=0;
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->column; ++j) {
            this_i_j=this->get(i,j);
            if(this_i_j==0){
                continue;
            }
            for (int k = 0; k < cm.column; ++k) {
                if(cm.get(j,k)==0){
                    continue;
                }
                output.dataptr->get_values_ptr()[i*cm.column+k]+=(float)(this_i_j*cm.get(j,k));
            }
        }
    }
    output.dataptr->setDefaultRef();
    return output;
}
CMatrix operator*(const CMatrix& cm,int x){
    CMatrix output(cm.row,cm.column);
    if(x==0){
        return output;
    }
    for (int i = 0; i < cm.row*cm.column; ++i) {
        output.dataptr->get_values_ptr()[i]=(cm.dataptr->get_values_ptr()[i]*(float)x);
    }
    output.dataptr->setDefaultRef();
    return output;
}
CMatrix operator*(int x,const CMatrix& cm){
    CMatrix output(cm.row,cm.column);
    if(x==0){
        return output;
    }
    for (int i = 0; i < cm.row*cm.column; ++i) {
        output.dataptr->get_values_ptr()[i]=(cm.dataptr->get_values_ptr()[i]*(float)x);
    }
    output.dataptr->setDefaultRef();
    return output;
}
CMatrix CMatrix::operator^(int x) const{
    if(this->row!=this->column){
        cerr<<"Not a square! No pow is allowed!"<<endl;
        return CMatrix(0,0);
    }else if(x<0){
        cerr<<"No negative pow is allowed!"<<endl;
        return CMatrix(0,0);
    }else{
        CMatrix pow=(*this);
        CMatrix output(this->row,this->row);
        output.setIdentity();
        while (x!=0){
            if((x&1)==1){
                output=output*(pow);
            }
            pow=(pow)*(pow);
            x>>=1;
        }
        output.dataptr->setDefaultRef();
        return output;
    }

}
CMatrix& CMatrix::operator=(const CMatrix& cm){
    if(this==(&cm)){
        return *this;
    }
    this->row=cm.row;
    this->column=cm.column;
    data_gc();
    this->dataptr=cm.dataptr;
    this->dataptr->addReference();
    return *this;
}
bool operator==(const CMatrix& cm1,const CMatrix& cm2){
    if(&cm1==&cm2){
        return true;
    }
    if(cm1.row!=cm2.row||cm1.column!=cm2.column){
        return false;
    }
    return memcmp(cm1.dataptr->get_values_ptr(),cm2.dataptr->get_values_ptr(),((long)sizeof(float))*(cm1.row)*(cm1.column))==0;
}
bool operator!=(const CMatrix& cm1,const CMatrix& cm2){
    return !(cm1==cm2);
}
void CMatrix::operator+=(const CMatrix& cm){
    *this=(*this)+cm;
}
void CMatrix::operator-=(const CMatrix& cm){
    *this+=(cm*-1);
}
void CMatrix::operator*=(const CMatrix& cm){
    *this=(*this)*cm;
}
void CMatrix::operator*=(const int x){
    *this=(*this)*x;
}
const float* CMatrix::operator[](int i){
    if(rangeCheck(i,0)){
        const float* ptr=&(dataptr->get_values_ptr()[i*column]);
        return ptr;
    }else{
        return nullptr;
    }
}

float CMatrix::get(int r, int c) const {
    if(!rangeCheck(r,c)){
        return 0.0f;
    }else{
        return this->dataptr->get_values_ptr()[r*this->column+c];
    }
}
void CMatrix::set(int r, int c,float value) {
    if(rangeCheck(r,c)){
        this->dataptr->get_values_ptr()[r*column+c]=value;
    }
}
int CMatrix::getRow() const{
    return this->row;
}
int CMatrix::getColumn() const{
    return column;
}
int CMatrix::getRef()const{
    return this->dataptr->getReference();
}
CMatrix CMatrix::clone() const {
    CMatrix c(this->row,this->column);
    memcpy(c.dataptr->get_values_ptr(),this->dataptr->get_values_ptr(),((long)sizeof(float))*this->row*this->column);
    return c;
}
void CMatrix::copyOf(const CMatrix &cm){
    if(this==(&cm)){
        return;
    }
    int r=cm.row;
    int c=cm.column;
    this->row=r;
    this->column=c;
    data_gc();
    this->dataptr=new Data(r*c);
    memcpy(this->dataptr->get_values_ptr(),cm.dataptr->get_values_ptr(),((long)sizeof(float))*r*c);
}

bool CMatrix::rangeCheck(int r, int c) const {
    if(r>=this->row||c>=this->column){
        cerr<<"Out of Range!"<<endl;
        return false;
    }else if(r<0||c<0){
        cerr<<"Negative Index!"<<endl;
        return false;
    }else{
        return true;
    }
}
void CMatrix::data_gc(){
    if(this->dataptr== nullptr){
        return;
    }
    if(this->dataptr->getReference()<=1){
        cout<<"Data has been garbage collected!"<<endl;
        delete this->dataptr;
    }else{
        this->dataptr->removeReference();
    }
}
void CMatrix::setIdentity(){
    // row == column is always true!
    // zero to identity
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->column; ++j) {
            if(i!=j){
                this->set(i,j,0);
            }
            this->set(i,j,1);
        }
    }
}


