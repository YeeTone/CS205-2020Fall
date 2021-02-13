#pragma GCC optimize(3,"Ofast","inline")
#include <iostream>
#include <ctime>
#include <windows.h>
#include <random>
#include "CMatrix.h"
using namespace std;

//MatrixA: m*n
//MatrixB: n*k
int m=0,n=0,k=0;
bool isRandom1= false,isRandom2=false;
unsigned long long xp=0,yp=0,zp=0;

CMatrix* cmPointer1= nullptr;
CMatrix* cmPointer2= nullptr;
CMatrix* cmResultPointer= nullptr;

bool isEnglish=true;

int main();
inline void checkIsUserRandom(int sign);
void improveCIO();
void cinSize(char sign);
inline void initiate();
inline void cinElement(int r,int c,int sign);
inline void cinAllElement(int sign);
inline float randomGenerate();
void printWelcome();
void printHelp();
inline void printExit();

int main() {
    improveCIO();
    printWelcome();
    string checkStr="Y";
    while(checkStr=="Y"){
        cinSize('m');
        cinSize('n');
        cinSize('k');
        checkIsUserRandom(1);
        checkIsUserRandom(2);
        initiate();
        long t3=clock();
        cinAllElement(1);
        cinAllElement(2);
        long t4=clock();
        cout<<"A:\n";
        cmPointer1->printCM();
        cout<<"B:\n";
        cmPointer2->printCM();

        if(isEnglish){
            cout<<"Data IO Time:"<<(t4-t3)<<"ms\n";
            cout<<"Matrix A(m*n):\n";
//          cmPointer1->printCM();
            cout<<"Matrix B(n*k):\n";
//          cmPointer2->printCM();
        }else{
            cout<<"数据输入时间:"<<(t4-t3)<<"ms\n";
            cout<<"矩阵 A(m*n):\n";
//          cmPointer1->printCM();
            cout<<"矩阵 B(n*k):\n";
//          cmPointer2->printCM();
        }


        if(m==n&&n==k){
            cout<<"A+B:\n";
            (*cmPointer1+*cmPointer2);
            cout<<"A-B:\n";
            (*cmPointer1-*cmPointer2);
        }
        long long t5=clock();
        cout<<"A*B:\n";
        *cmResultPointer=((*cmPointer1)*(*cmPointer2));
        cmResultPointer->printCM();
        long long t6=clock();
        if(isEnglish){
            cout<<"Multiplication Time:"<<(t6-t5)<<"ms\n";
            cout<<"Do you want to calculate again? Print[Y] to continue.\n";
        }else{
            cout<<"矩阵乘法时间："<<(t6-t5)<<"ms\n";
            cout<<"还需要继续计算吗？输入[Y]以继续。";
        }
        cin>>checkStr;
    }
    return 0;
}
inline void improveCIO(){
    SetConsoleOutputCP(65001);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr.tie(nullptr);
    CMatrix::isExpressedOmitted=true;
//    ios::sync_with_stdio(false); // Unknown Error
//    cout.setf(ios::fixed,ios::floatfield);
}
void cinSize(char sign){
    int number=0;
    string input;

    while(true){
        try{
            if(isEnglish){
                cout<<"Please input for "<<sign<<"\n";
            }else{
                cout<<"请输入矩阵大小描述元素"<<sign<<"\n";
            }
            cin>>input;
            if(input=="Chinese"){
                cout<<"中文设置成功！\n";
                isEnglish=false;
                continue;
            }else if(input=="English"){
                cout<<"English is set successfully!\n";
                isEnglish=true;
                continue;
            }else if(input=="welcome"){
                printWelcome();
                continue;
            }else if(input=="help"){
                printHelp();
                continue;
            }else if(input=="exit"){
                printExit();
                continue;
            }else if(input=="omit"){
                if(isEnglish){
                    cout<<"Some elements of the matrix is omitted when showing.\n";
                }else{
                    cout<<"矩阵显示模式为部分省略。\n";
                }
                CMatrix::isExpressedOmitted=true;
                continue;
            }else if(input=="all"){
                if(isEnglish){
                    cout<<"All elements of the matrix will be diaplayed when showing.\n";
                }else{
                    cout<<"矩阵显示模式为全部展示。\n";
                }
                CMatrix::isExpressedOmitted=false;
                continue;
            }
            for (char& c:input){
                if(!isdigit(c)){
                    throw invalid_argument("No digit!");
                }
            }
            number=stoi(input);
            if(number<=0){
                if(isEnglish){
                    throw out_of_range("The number is not positive!\n");
                }else{
                    throw out_of_range("输入的数字不是一个正数！\n");
                }
            }
            else if(number>25000){
                if(isEnglish){
                    throw out_of_range("The number is too large! Out of Memory!\n");
                }else{
                    throw out_of_range("输入数字过大！可能内存超限！\n");
                }
            }
            break;
        } catch (invalid_argument& ia_error) {
            if(isEnglish){
                cerr<<"You have input something wrong!\n";
            }else{
                cerr<<"输入错误！请重新输入！\n";
            }

            continue;
        } catch (out_of_range& or_error) {
            cerr<<or_error.what();
        }
    }

    switch (sign) {
        case 'm':{
            m=number;
            break;
        }
        case 'n':{
            n=number;
            break;
        }
        default:{
            k=number;
            break;
        }
    }
}
inline void initiate(){
    default_random_engine e;
    e.seed(time(nullptr));
    uniform_int_distribution<unsigned> u(0, INT_MAX);
    xp=u(e);
    yp=u(e);
    zp=u(e);
    cout<<xp<<" "<<yp<<" "<<zp<<"\n";
    delete cmPointer1;
    delete cmPointer2;
    delete cmResultPointer;
    cmPointer1=new CMatrix(m,n);
    cmPointer2=new CMatrix(n,k);
    cmResultPointer=new CMatrix(m,k);
}
void cinElement(int r,int c,int sign){
    string input;
    float number=0;
    while (true){
        try {
            cout<<"Please input for matrix"<<sign<<"["<<r<<"]["<<c<<"]\n";
            cin>>input;
            if(input=="Chinese"){
                cout<<"中文设置成功！\n";
                isEnglish=false;
                continue;
            }else if(input=="English"){
                cout<<"English is set successfully!\n";
                isEnglish=true;
                continue;
            }else if(input=="welcome"){
                printWelcome();
                continue;
            }else if(input=="help"){
                printHelp();
                continue;
            }else if(input=="exit"){
                printExit();
                continue;
            }else if(input=="omit"){
                if(isEnglish){
                    cout<<"Some elements of the matrix is omitted when showing.\n";
                }else{
                    cout<<"矩阵显示模式为部分省略。\n";
                }
                CMatrix::isExpressedOmitted=true;
                continue;
            }else if(input=="all"){
                if(isEnglish){
                    cout<<"All elements of the matrix will be diaplayed when showing.\n";
                }else{
                    cout<<"矩阵显示模式为全部展示。\n";
                }
                CMatrix::isExpressedOmitted=false;
                continue;
            }
            int minusTime=0;
            int dotTime=0;
            for(char& ct:input){
                if(!isdigit(ct)){
                    if(ct=='-'){
                        if(minusTime!=0){
                            throw invalid_argument("");
                        }else{
                            minusTime+=1;
                        }
                    }
                    else if(ct=='.'){
                        if(dotTime!=0){
                            throw invalid_argument("");
                        }else{
                            dotTime+=1;
                        }
                    }
                    else{
                        throw invalid_argument("");
                    }
                }
            }
            number=stof(input);
            break;
        } catch (invalid_argument& ia_error) {
            if(isEnglish){
                cerr<<"You have input something wrong!\n";
            }else{
                cerr<<"输入错误！请重新输入！\n";
            }
            continue;
        } catch (out_of_range& or_error) {
            if(isEnglish){
                cerr<<"The input is too large!\n";
            }else{
                cerr<<"输入数值过大！请重新输入！\n";
            }
            continue;
        }
    }
    if(sign==1){
        if(r>=m||c>=n){
            if(isEnglish){
                cerr<<"Matrix Out of Bound!\n";
            }else{
                cerr<<"矩阵赋值越界！\n";
            }

            return;
        }
        cmPointer1->set(r,c,number);
    }else{
        if(r>=n||c>=k){
            if(isEnglish){
                cerr<<"Matrix Out of Bound!\n";
            }else{
                cerr<<"矩阵赋值越界！\n";
            }
            return;
        }
        cmPointer2->set(r,c,number);
    }

}
inline float randomGenerate(){
    xp^=xp<<3;
    xp^=xp>>7;
    xp^=xp<<1;
    unsigned long long t=xp;
    xp=yp;
    yp=zp;
    zp=t^xp^yp;
    return zp*1.0f/INT16_MAX;
}
void cinAllElement(int sign){
    if(sign==1){
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(isRandom1){
                    cmPointer1->set(i,j,randomGenerate());
                }else{
//                    cmPointer1->set(i,j,3);
                    cinElement(i,j,sign);

                }
            }
        }
    }else{
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                if(isRandom2){
                    cmPointer2->set(i,j,randomGenerate());
                }else{
//                    cmPointer2->set(i,j,3);
                    cinElement(i,j,sign);
                }
            }
        }
    }
}
inline void checkIsUserRandom(int sign){
    if(isEnglish){
        cout<<"If you want to make matrix"<<sign<<" be a random matrix? If so, please print[Y].\n";
    }else{
        cout<<"你是否要让矩阵"<<sign<<"是一个随机矩阵？如果是的话，请输入[Y].\n";
    }
    string input;
    cin>>input;
    if(sign==1){
        isRandom1=(input=="Y");
    }else{
        isRandom2=(input=="Y");
    }

}
void printWelcome(){
    if(isEnglish){
        cout<<"-------------------------------------\n";
        cout<<"Welcome using this Matrix calculator!\n";
        cout<<"This calculator is mainly for C/C++ Midterm Project: Matrix Multiplication.\n";
        cout<<"This calculator is the combination of Assignment2 and Assignment3, so it is much better than that in Assignment3\n";
        cout<<"University: SUSTech\n";
        cout<<"Course: CS205(C/C++ Program Design)\n";
        cout<<"Course Instructor: Shiqi Yu\n";
        cout<<"Author: YeeTone Wang\n";
        cout<<"SID: 11910104\n";
        cout<<"Version: 1.23\n";
        cout<<"If you need help, please print help to get some helpful information.\n";
        cout<<"If you need welcome, please print welcome to get this information again.\n";
        cout<<"If you need exit, please print exit to get exit information.\n";
        cout<<"Print omit to omit some elements of matrix when showing, if the matrix is too large.\n";
        cout<<"Print all to show all elements of matrix so that you can see the elements thoroughly.\n";
        cout<<"[Contact me by email: 11910104@mail.sustech.edu.cn\n";
        cout<<"如果需要显示中文，请输入Chinese.\n";
        cout<<"-------------------------------------\n";
        cout<<"Please enjoy your matrix calculation!\n";
    }else{
        cout<<"-------------------------------------\n";
        cout<<"欢迎使用本矩阵计算器！\n";
        cout<<"本计算器主要是用于C/C++期中Project————矩阵乘法。\n";
        cout<<"本计算器是Assignment2和Assignment3的结合升级产品，因此它比Assignment3的向量乘法器要强大很多！\n";
        cout<<"学校：南方科技大学\n";
        cout<<"课程：CS205(C/C++程序设计)\n";
        cout<<"课程教师：于仕琪\n";
        cout<<"作者：王奕童\n";
        cout<<"学号：11910104\n";
        cout<<"版本：1.23\n";
        cout<<"如果需要计算器的使用说明，请输入help\n";
        cout<<"如果需要计算器的欢迎信息，请输入welcome以重新获取本信息\n";
        cout<<"如果需要退出，请输入exit以退出\n";
        cout<<"输入omit以在矩阵过大时省略部分矩阵元素的输出\n";
        cout<<"输入all以全部展示矩阵元素\n";
        cout<<"【联系作者：11910104@mail.sustech.edu.cn\n】";
        cout<<"If you need to show these information in English, please print English.\n";
        cout<<"-------------------------------------\n";
        cout<<"开始运算吧！\n";
    }
}
void printHelp(){
    cout<<"-----------------------------------------\n";
    if(isEnglish){
        cout<<"This is the help for the calculator user!\n";
        cout<<"Author: YeeTone Wang\n";
        cout<<"Version: 1.23\n";
        cout<<"1.Language change:\n";
        cout<<"Any time, if you like, you can input English to change the calculator into the English verison.\n";
        cout<<"On the contrary, you can change it into Chinese verison by inputting Chinese.\n";
        cout<<"2.Input the size of matrix:\n";
        cout<<"You are asked to input 3 integer variables:m,n,k\n";
        cout<<"There are 2 matrix in total: A(m*n) and B(n*k)\n";
        cout<<"Hint: m,n,k∈(0,25000]\n";
        cout<<"3.Choose if random:\n";
        cout<<"You can let the calculator produce the random matrix through XORShift Algorithm.\n";
        cout<<"Therefore, you don't need to input the element by yourself!\n";
        cout<<"4.Input your elements:\n";
        cout<<"This is very simple. Just follow the guideline on the command line.\n";
    }else{
        cout<<"这是关于此计算器的简单使用说明\n";
        cout<<"作者：王奕童\n";
        cout<<"版本：1.23\n";
        cout<<"1.语言切换\n";
        cout<<"任意时刻，你可以输入English来切换到英文版本\n";
        cout<<"相反地，你可以通过输入Chinese来切换到中文版本\n";
        cout<<"2.输入矩阵大小\n";
        cout<<"你可以输入3个整数m,n,k来规定矩阵的大小\n";
        cout<<"总共有2个矩阵：A(m*n)和B(n*k)\n";
        cout<<"提示：m,n,k∈(0,25000]\n";
        cout<<"3.选择是否是随机数模式：\n";
        cout<<"你可以让计算器自行通过XORShift算法来快速生成随机矩阵元素\n";
        cout<<"这样一来，你就不用手动输入矩阵元素了！\n";
        cout<<"4.输入矩阵元素：\n";
        cout<<"这超简单的！只要跟着屏幕上的说明走就好了！\n";
    }
    cout<<"-----------------------------------------\n";
}
void printExit(){
    string input;
    if(isEnglish){
        cout<<"Are you sure to exit? Print[Y] to exit, otherwise will return\n";
    }else{
        cout<<"你是否确定退出？坚持退出则请再输入[Y]，否则将返回。\n";
    }
    cin>>input;
    if(input=="Y"){
        exit(0);
    }else{
        return;
    }
}