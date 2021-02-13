#include <iostream>
#include "CMatrix.h"
#include <memory>
using namespace std;

void instruction();
void test_case1();
void test_case2();
void test_case3();
void test_case4();
void test_case5();
void test_case6();

int main() {
    instruction();
    return 0;
}

void instruction(){
    cout<<"In these test cases, we use cout<<cm to show the matrix elements."<<endl;
    cout<<"Thus, you can find that operator<< can be used correctly."<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    int choice=0;
    cout<<"Please give the test case number, 1~6 are available."<<endl;
    cin>>choice;
    switch (choice) {
        case 1:{
            test_case1();
            return;
        }
        case 2:{
            test_case2();
            return;
        }
        case 3:{
            test_case3();
            return;
        }
        case 4:{
            test_case4();
            return;
        }
        case 5:{
            test_case5();
            return;
        }
        case 6:{
            test_case6();
            return;
        }
        default:{
            return;
        }
    }
}
void test_case1(){
    cout<<"This is the test case#1 for constructor CMatrix(int r=0, int c=0)"<<endl;
    CMatrix cm1;
    cout<<cm1;
    CMatrix cm2(2,3);
    cout<<cm2;
}
void test_case2(){
    cout<<"This is the test case#2 for constructor CMatrix(int r,int c,const float* outData)"<<endl;
    auto* values=new float[6]();
    for (int i = 0; i < 6; ++i) {
        values[i]=(float)i*1.0f+1;
    }
    CMatrix cm(2,3,values);
    cout<<cm;
}
void test_case3(){
    cout<<"This is the test case#3 for overloading copy constructor CMatrix(const CMatrix& cm)"<<endl;
    float values[3]={1.0,2.0,3.0};
    CMatrix cm(1,3,values);
    cout<<"stdCM has been created."<<endl;
    cout<<"cm:"<<cm;
    CMatrix cm2(cm);
    CMatrix cm3(cm);
    CMatrix cm4(cm);
    cout<<"Now another 3 matrix using CMatrix(const CMatrix& cm) are created."<<endl;
}
void test_case4(){
   cout<<"This is the test case#4 for destructor ~CMatrix() and operator="<<endl;
   float values[6]={1.0,2.0,3.0,
                     4.0,5.0,6.0};
   CMatrix stdMatrix(2,3,values);
   cout<<"Now stdMatrix 3x2 has been created!"<<endl;
   cout<<stdMatrix;
   CMatrix cm1;
   CMatrix cm2;
   CMatrix cm3;
   cm1=cm2=cm3=stdMatrix;
   cout<<"3 Matrixes using = has been created as well!"<<endl;

}
void test_case5(){
    cout<<"This is the test case#5 for operator* overloading: A*B"<<endl;
    float values[6]={1.0,2.0,3.0,
                     4.0,5.0,6.0};
    CMatrix cm1(2,3,values);
    CMatrix cm2(3,2,values);
    cout<<"CMatrix1:"<<cm1;
    cout<<"CMatrix2:"<<cm2;
    cout<<(cm1*cm2)<<endl;
}
void test_case6(){
    cout<<"This is the test case#6 for operator* overloading: A*b and a*B"<<endl;
    float values[6]={1.0,2.0,3.0,
                     4.0,5.0,6.0};
    CMatrix cm1(2,3,values);
    cout<<"cmatrix:"<<cm1;
    cout<<"------------"<<endl;
    cout<<"2*cmatrix:"<<2*cm1;
    cout<<"------------"<<endl;
    cout<<"cmatrix*2:"<<cm1*2;
}