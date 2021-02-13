#pragma GCC optimize(3,"Ofast","inline")
#include <iostream>
#include <windows.h>
#include "CMatrix.h"

void improveCIO();
void test_case_select();
void test_case1();
void test_case2();
void test_case3();
void test_case4();
void test_case7();
void test_case8();
void test_case9();
void test_case10();
void test_case11();
void test_case12();
void test_case13();
void test_case14();
void test_case15();
void test_case16();
void test_case17();
void test_case18();
void test_case19();

int main() {
    improveCIO();
    test_case_select();
    return 0;
}
void improveCIO(){
    SetConsoleOutputCP(65001);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr.tie(nullptr);
    CMatrix::isExpressedOmitted=true;
}
void test_case_select(){
    cout<<"Please input the test case number:\n";
    cout<<"1-4, 7-19 are available.\n";
    int n;
    cin>>n;
    switch (n) {
        case 1:{
            test_case1();
            break;
        }
        case 2:{
            test_case2();
            break;
        }
        case 3:{
            test_case3();
            break;
        }
        case 4:{
            test_case4();
            break;
        }
        case 7:{
            test_case7();
            break;
        }
        case 8:{
            test_case8();
            break;
        }
        case 9:{
            test_case9();
            break;
        }
        case 10:{
            test_case10();
            break;
        }
        case 11:{
            test_case11();
            break;
        }
        case 12:{
            test_case12();
            break;
        }
        case 13:{
            test_case13();
            break;
        }
        case 14:{
            test_case14();
            break;
        }
        case 15:{
            test_case15();
            break;
        }
        case 16:{
            test_case16();
            break;
        }
        case 17: {
            test_case17();
            break;
        }
        case 18:{
            test_case18();
            break;
        }
        case 19:{
            test_case19();
            break;
        }
        default:{
            return;
        }
    }
}

void test_case1(){
    auto* cmPointer1=new CMatrix(1,3);
    auto* cmPointer2=new CMatrix(3,1);
    for (int i = 0; i < 3; ++i) {
        cmPointer1->set(0,i,(float)(i+1));
        cmPointer2->set(i,0,(float)(i+1));
    }
    cout<<"A:\n";
    cmPointer1->printCM();
    cout<<"B:\n";
    cmPointer2->printCM();
    cout<<"A*B:\n";
    CMatrix out=(*cmPointer1)*(*cmPointer2);
    out.printCM();
    delete cmPointer1;
    delete cmPointer2;
}
void test_case2(){
    auto* cmPointer1=new CMatrix(3,3);
    auto* cmPointer2=new CMatrix(3,3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cmPointer1->set(i,j,(float)(i*3+j+1));
            cmPointer2->set(i,j,(float)(10-(i*3+j+1)));
        }
    }
    cout<<"A:\n";
    cmPointer1->printCM();
    cout<<"B:\n";
    cmPointer2->printCM();
    CMatrix out=(*cmPointer1)*(*cmPointer2);
    out.printCM();
    delete cmPointer1;
    delete cmPointer2;
}
void test_case3(){
    auto* cmPointer1=new CMatrix(5,5);
    auto* cmPointer2=new CMatrix(5,5);
    for (int i = 0; i < 5; ++i) {
        cmPointer1->set(0,i,(float)(i+1));
        cmPointer2->set(i,0,(float)(i+1));
    }
    cout<<"A:\n";
    cmPointer1->printCM();
    cout<<"B:\n";
    cmPointer2->printCM();
    cout<<"A*B:\n";
    CMatrix out=(*cmPointer1)*(*cmPointer2);
    out.printCM();
    delete cmPointer1;
    delete cmPointer2;
}
void test_case4(){
    auto* cmPointer1=new CMatrix(1,3);
    auto* cmPointer2=new CMatrix(2,1);
    ((*cmPointer1)*(*cmPointer2)).printCM();
    delete cmPointer1;
    delete cmPointer2;
}
void test_case7(){
    auto* cmPointer1=new CMatrix(1,200000000);
    auto* cmPointer2=new CMatrix(200000000,1);
    cmPointer1->fill(1);
    cmPointer2->fill(1);
    cmPointer1->printCM();
    cmPointer2->printCM();
    ((*cmPointer1)*(*cmPointer2)).printCM();
    delete cmPointer1;
    delete cmPointer2;
}
void test_case8(){
    auto* cmPointer1=new CMatrix(1024,1024);
    auto* cmPointer2=new CMatrix(1024,1024);
    cmPointer1->set(0,0,4);
    cmPointer1->set(0,1,2);
    cmPointer1->set(1,0,2);
    cmPointer1->set(1,1,4);
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cmPointer2->set(0,0,1);
    cmPointer2->set(0,1,3);
    cmPointer2->set(1,0,3);
    cmPointer2->set(1,1,1);
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case9(){
    auto* cmPointer1=new CMatrix(1024,1024);
    auto* cmPointer2=new CMatrix(1024,1024);
    cmPointer1->fill(3);
    cmPointer2->setDiagonal(2);
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case10(){
    auto* cmPointer1=new CMatrix(1024,1024);
    auto* cmPointer2=new CMatrix(1024,1024);
    cmPointer1->setDiagonal(3);
    cmPointer2->setDiagonal(2);
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case11(){
    auto* cmPointer1=new CMatrix(4096,4096);
    auto* cmPointer2=new CMatrix(4096,4096);
    cmPointer1->setDiagonal(1);
    cmPointer2->fill(996);
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case12(){
    auto* cmPointer1=new CMatrix(1024,1024);
    auto* cmPointer2=new CMatrix(1024,1024);
    cmPointer2->fill(996);
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case13() {
    auto *cmPointer1 = new CMatrix(15000, 15000);
    auto *cmPointer2 = new CMatrix(15000, 15000);
    for (int i = 0; i < 15000; ++i) {
        for (int j = 0; j < 15000; ++j) {
            cmPointer1->set(i,j,rand());
            cmPointer2->set(i,j,rand());
        }
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case14(){
    auto *cmPointer1 = new CMatrix(15000, 15000);
    auto *cmPointer2 = new CMatrix(15000, 15000);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cmPointer1->set(i,j,i*3+j);
        }
    }
    for (int i = 0; i < 15000; ++i) {
        for (int j = 0; j < 15000; ++j) {
            cmPointer2->set(i,j,rand());
        }
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case15(){
    auto *cmPointer1 = new CMatrix(15000, 15000);
    auto *cmPointer2 = new CMatrix(15000, 15000);
    for (int i = 0; i < 15000; ++i) {
        cmPointer1->set(i,i,i+1);
    }
    for (int i = 0; i < 15000; ++i) {
        for (int j = 0; j < 15000; ++j) {
            cmPointer2->set(i,j,rand());
        }
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case16(){
    auto *cmPointer1 = new CMatrix(1, 2e+8);
    auto *cmPointer2 = new CMatrix(2e+8, 1);
    for (int i = 0; i < 2e+8; ++i) {
        cmPointer1->set(0,i,i+1);
        cmPointer2->set(i,0,2e+8-i);
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case17(){
    auto *cmPointer1 = new CMatrix(15000, 15000);
    auto *cmPointer2 = new CMatrix(15000, 15000);
    *cmPointer1=CMatrix::getIdentical(15000);
    for (int i = 0; i < 15000; ++i) {
        for (int j = 0; j < 15000; ++j) {
            cmPointer2->set(i,j,rand());
        }
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case18(){
    auto *cmPointer1 = new CMatrix(15000, 15000);
    auto *cmPointer2 = new CMatrix(15000, 15000);
    *cmPointer1=CMatrix::getZeros(15000,15000);
    for (int i = 0; i < 15000; ++i) {
        for (int j = 0; j < 15000; ++j) {
            cmPointer2->set(i,j,rand());
        }
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}
void test_case19() {
    auto *cmPointer1 = new CMatrix(5000, 5000);
    auto *cmPointer2 = new CMatrix(5000, 5000);
    for (int i = 0; i < 5000; ++i) {
        for (int j = 0; j < 5000; ++j) {
            cmPointer1->set(i,j,rand());
            cmPointer2->set(i,j,rand());
        }
    }
    cout<<"A:"<<endl;
    cmPointer1->printCM();
    cout<<"B:"<<endl;
    cmPointer2->printCM();
    long t1=clock();
    cout<<"A*B:"<<endl;
    ((*cmPointer1)*(*cmPointer2)).printCM();
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
    delete cmPointer1;
    delete cmPointer2;
}