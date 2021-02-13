#include<iostream>
#include<algorithm>
#include<stack>
#include<stdlib.h>
#include<vector>
#include<string>
#include <cctype>
#include <string.h>
#include <math.h>
#include <locale>


#ifdef _WIN32
#include <windows.h>
#endif

#include "CWTNumber.h"
#include "Variable.h"
#pragma execution_character_set("utf-8")

using namespace std;
static bool isEnglish=true;

template <typename T> class ArrayList;

int main();

static inline string clearEmptySpace(string expression);
//clear all empty space in the expression.
static inline bool isBracketMatching(string expression);
//to check if the left bracker( and right bracket) is matched.
static inline string format(string expression);
//to pretreat some basic case like -1+3
static inline int prior(char op);
//to get the priority of operator
static inline vector<string> middleToBack(string expression);
static inline string result(vector<string> bh);
/* Middle expression to the back expression:
 * For example:
 * a + b*c + (d * e + f) * g --->>> a b c * + d e * f  + g * +
 * */
static inline string solve(string expression);
//the method to solve the back-expression to the correct result.


static inline bool checkUnknownVar(string expression);
//is there any unknown variable in the expression. If , then cerr << a message.
static inline bool isAssigning(string expression);
//to check if the expression is for assigning
static inline void addVariable(string expression);
//to add some variables ArrayList.
static inline string replaceVar(string expression);
//to replace the variables in the expression.
static inline string pretreat(string expression);


static inline bool containsCertainMathFunctions(string expression,string funName);
//check if certain function name is contained in the expression
static inline string replaceAllMathFunctions(string expression);
//if contains, then replace it into real value.

//These functions are to add annotations.
static inline bool isSingleAnnotation(string expression);
static inline bool isMutipleAnnotationStart(string expression);
static inline bool isMutipleAnnotationEnd(string expression);

//Print help list
static inline void printHelpEnglish();
static inline void printWelcomeEnglish();
static inline void printHelpChinese();
static inline void printWelcomeChinese();


template <typename T> class ArrayList{
private:
    T value[1000];
    int size;
public:
    ArrayList(){
        size=0;
    }
    void add(T t){
        value[size]=t;
        size++;
    }
    T get(int index){
        return value[index];
    }
    void set(int index,T t){
        if(index==0||index==1){
            if(isEnglish){
                cerr<<"This is constant value. Cannot be changed!"<<endl;
            } else{
                cerr<<"这是一个常量。禁止修改！"<<endl;
            }

            //0-E=2.718281828459
            //1-PI=3.1415926535898
            return;
        }
        value[index]=t;
    }
    int getSize(){
        return size;
    }

    bool contains(T t){
        return indexOf(t)!=-1;
    }
    bool isEmpty(){
        return size==0;
    }
    int indexOf(T t){
        for (int i = 0; i < size; ++i) {
            if(value[i]==t){
                return i;
            }
        }
        return -1;
    }
};

static bool isMutipleAnnotating= false;
//To check the annotating case of /* and */
static ArrayList<string> varNameList;
//ArrayList to store variable's name
static ArrayList<string> valueList;
//ArrayList to store value
const static CWTNumber Zero("0");
//const value of "0"


int main() {
    SetConsoleOutputCP (65001);

    printWelcomeEnglish();
    varNameList.add("E");
    valueList.add("2.718281828459");
    varNameList.add("PI");
    valueList.add("3.1415926535898");
    string str;
    bool isExiting= false;

    while(getline(cin,str)){
        if(isExiting){
            if(str=="Y"){
                break;
            } else{
                cout<<"-------------------------------------"<<endl;
                if(isEnglish){
                    cout<<"Please enjoy your calculation!"<<endl;
                } else{
                    cout<<"开始运算吧！"<<endl;
                }

                isExiting= false;
                continue;
            }
        }
        if(str=="Chinese"){
            isEnglish= false;
            cout<<"中文设置成功！"<<endl;
            continue;
        } else if(str=="English"){
            isEnglish=true;
            cout<<"English is set successfully!"<<endl;
            continue;
        }
        if(str=="exit"){
            if(isEnglish){
                cout<<"Are you sure to exit? Print[Y] to exit, otherwise will return"<<endl;
            } else{
                cout<<"确认退出吗？在屏幕中输入[Y]则退出，否则将返回"<<endl;
            }
            isExiting=true;
            continue;
        }
        str=clearEmptySpace(str);
        if(isMutipleAnnotationEnd(str)){
            isMutipleAnnotating= false;
        }else if(isSingleAnnotation(str)){
            continue;
        } else if(isMutipleAnnotationStart(str)){
            isMutipleAnnotating=true;
            continue;
        }

        if(isMutipleAnnotating){
            continue;
        }

        if(str=="help"){
            if(isEnglish){
                printHelpEnglish();
            } else{
                printHelpChinese();
            }

            continue;
        } else if(str=="welcome"){
            if(isEnglish){
                printWelcomeEnglish();
            } else{
                printWelcomeChinese();
            }
            continue;
        }

        if(!isBracketMatching(str)){
            if(isEnglish){
                cerr<<"The bracket is not matching!"<<endl;
            } else{
                cerr<<"左右括号不匹配！"<<endl;
            }

            continue;
        }
        try {
            if(isAssigning(str)){
                addVariable(str);
                continue;
            }
        }catch (exception e1){
            if(isEnglish){
                cerr<<"The variable name is not valid!"<<endl;
            } else{
                cerr<<"变量名不合法！"<<endl;
            }

            continue;
        }
        str=pretreat(str);
        str=replaceAllMathFunctions(str);;
        str=replaceVar(str);
        str=pretreat(str);
        if(!checkUnknownVar(str)){
            if(isEnglish){
                cerr<<"The variable does not exist!"<<endl;
            } else{
                cerr<<"变量不存在！"<<endl;
            }
            continue;
        }

        cout <<solve(str)<<endl;
    }
    return 0;
}

string clearEmptySpace(string expression){
    string cleared;
    for (int i = 0; i < expression.length(); ++i) {
        if(expression[i]!=' '){
            cleared+=expression[i];
        }
    }
    return cleared;
}
bool isBracketMatching(string expression){
    int left=0,right=0;
    for (int i = 0; i < expression.length(); ++i) {
        if(expression[i]=='('){
            left++;
        } else if(expression[i]==')'){
            right++;
        }
    }
    return left==right;
}
string format(string expression){
    for(int i = 0;i < expression.length(); i++){
        if(expression[i] == '-'){
            if(i == 0){
                expression.insert(0,1,'0');
            }else if(expression[i-1] == '('){
                expression.insert(i,1,'0');
            }
        }

    }
    return expression;
}
int prior(char op){
    if(op == '+' || op == '-'){
        return 1;
    }else if(op == '*' || op == '/'){
        return 2;
    }else{
        return 0;
    }

}
vector<string> middleToBack(string expression){
    vector<string> vs;
    stack<char> st;
    for(int i = 0;i < expression.length(); i++){
        string tmp;
        switch(expression[i]){
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                if(st.empty() || st.top() == '('){
                    st.push(expression[i]);
                }else{
                    while(!st.empty() && prior(st.top()) >= prior(expression[i]) ){
                        tmp += st.top();
                        vs.push_back(tmp);
                        st.pop();
                        tmp = "";
                    }
                    st.push(expression[i]);
                }
                break;
            case '(':
                st.push(expression[i]);
                break;
            case ')':
                while(st.top() != '('){
                    tmp += st.top();
                    vs.push_back(tmp);
                    st.pop();
                    tmp = "";
                }
                st.pop();
                break;
            default:
                if((expression[i]>='0' && expression[i]<='9')){
                    tmp += expression[i];
                    while((i+1<expression.size() && expression[i+1]>='0' && expression[i+1]<='9')||expression[i+1] == '.')
                    {
                        tmp += expression[i+1];
                        ++i;
                    }
                    vs.push_back(tmp);
                }
        }
    }
    while(!st.empty()){
        string tmp;
        tmp += st.top();
        vs.push_back(tmp);
        st.pop();
    }
    return vs;
}

string result(vector<string> bh){
    stack<string> st;
    string num,op1,op2;
    for(int i = 0;i < bh.size(); i++){
        string tmp = bh[i];
        if(tmp[0] >= '0'&&tmp[0] <= '9'){
            st.push(tmp);
        }
        else if(bh[i]=="+")
        {
            CWTNumber cn1(st.top().c_str());
            st.pop();
            CWTNumber cn2(st.top().c_str());
            st.pop();
            st.push((cn1+cn2).toString());
        }
        else if(bh[i]=="-")
        {
            CWTNumber cn2(st.top().c_str());
            st.pop();
            CWTNumber cn1(st.top().c_str());
            st.pop();
            st.push((cn1-cn2).toString());
        }
        else if(bh[i]=="*")
        {
            CWTNumber cn1(st.top().c_str());
            st.pop();
            CWTNumber cn2(st.top().c_str());
            st.pop();
            st.push((cn1*cn2).toString());
        }
        else if(bh[i]=="/")
        {
            CWTNumber cn2(st.top().c_str());
            st.pop();
            CWTNumber cn1(st.top().c_str());
            st.pop();
            st.push((cn1/cn2).toString());
            if(cn2==Zero){
                return "#INFINITE";
            }
        }
    }
    return st.top();
}
string solve(string expression){
    if(expression=="nan"){
        return expression;
    }
    expression=replaceVar(expression);
    expression = format(expression);
    vector<string> bh = middleToBack(expression);
    string k = result(bh);
    return k;
}
bool checkUnknownVar(string expression){
    for (int i = 0; i < expression.length(); ++i) {
        if(!(isdigit(expression[i])||expression[i]=='.'
        ||expression[i]=='+'||expression[i]=='-'||expression[i]=='*'||expression[i]=='/'
        ||expression[i]=='('||expression[i]==')')){
            return false;
        }
    }
    return true;
}
bool isAssigning(string expression){
    int indexOfAssign=expression.find('=');
    if(indexOfAssign!=-1){
        string var=expression.substr(0,indexOfAssign);
        bool varNameValid=true;
        //check varName isValid start.
        //throw an exception if not valid.
        if(!(isalpha(var[0])||var[0]=='_')){
            varNameValid= false;
        }
        for (int i = 1; i < var.length(); ++i) {
            if(!(isdigit(var[i])||isalpha(var[i])||var[i]=='_')){
                varNameValid= false;
                break;
            }
        }
        if(!varNameValid){
            throw exception();
        }
        //check varName isValid
        return true;
    }
    return false;
}
void addVariable(string expression){
    int index=expression.find('=');
    string varName=expression.substr(0,index);
    string valStr=expression.substr(index+1);
    valStr=replaceAllMathFunctions(valStr);
    bool contains= false;
    for (int i = 0; i < varNameList.getSize(); ++i) {
        if(varNameList.get(i)==varName){
            contains=true;
            break;
        }
    }
    if(contains){
        int index=0;
        for (int i = 0; i < varNameList.getSize(); ++i) {
            if(varNameList.get(i)==varName){
                index=i;
                break;
            }
        }
        valueList.set(index,valStr);
    } else{
        varNameList.add(varName);
        valueList.add(valStr);
    }
}
string replaceVar(string expression){
    for (int i = 0; i < varNameList.getSize(); ++i) {
        while(expression.find(varNameList.get(i))!=-1){
            int index=expression.find(varNameList.get(i));
            string before=expression.substr(0,index);
            string after=expression.substr(index+varNameList.get(i).length());
            expression=before+valueList.get(i)+after;
        }
    }
    return expression;
}
string pretreat(string expression){
    int index1;
    do{
        index1=expression.find("+-");
        if(index1==-1){
            break;
        }
        expression=expression.substr(0,index1+1)+"0"+expression.substr(index1+1);
    }while (index1!=-1);

    return expression;
}

bool containsCertainMathFunctions(string expression,string funName){
    return expression.find(funName)!=-1;
}

string replaceAllMathFunctions(string expression){
    if(expression=="nan"){
        return expression;
    }
    expression=replaceVar(expression);
    while (containsCertainMathFunctions(expression,"sqrt(")){
        int left=expression.find("sqrt(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }

        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);
        string previous1 = expression.substr(left + 4,right-left-3);

        CWTNumber value(solve(previous1).c_str());
        if(value<Zero){
            expression="nan";
            return expression;
        }
        string middle=to_string(sqrt(stod(value.toString())));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"pow(")){
        int left=expression.find("pow(");
        int right=left,comma=left;
        for (int i = left; i < expression.length(); i++) {
            if(expression[i]==','){
                comma=i;
            }
            else if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous1 = expression.substr(left + 4,comma-left - 4);
        string previous2=expression.substr(comma+1,right-comma-1);

        CWTNumber value1(solve(previous1).c_str());
        CWTNumber value2(solve(previous2).c_str());
        string middle=to_string(pow(stod(value1.toString()),stod(value2.toString())));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"max(")){
        int left=expression.find("max(");
        int right=left,comma=left;
        for (int i = left; i < expression.length(); i++) {
            if(expression[i]==','){
                comma=i;
            }
            else if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous1 = expression.substr(left + 4,comma-left - 4);
        string previous2=expression.substr(comma+1,right-comma-1);

        string middle=CWTNumber(previous1.c_str())
                >CWTNumber(previous2.c_str())?CWTNumber(previous1.c_str()).toString():CWTNumber(previous2.c_str()).toString();
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"min(")){
        int left=expression.find("min(");
        int right=left,comma=left;
        for (int i = left; i < expression.length(); i++) {
            if(expression[i]==','){
                comma=i;
            }
            else if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous1 = expression.substr(left + 4,comma-left - 4);
        string previous2=expression.substr(comma+1,right-comma-1);

        string middle=CWTNumber(previous1.c_str())
                      <CWTNumber(previous2.c_str())?CWTNumber(previous1.c_str()).toString():CWTNumber(previous2.c_str()).toString();
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"abs(")){
        int left=expression.find("abs(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous = expression.substr(left + 4,right-left - 4);

        CWTNumber value(solve(previous).c_str());
        if(value<Zero){
            value=CWTNumber("-1")*value;
        }
        string middle=value.toString();
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"random()")){
        int left=expression.find("random(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string middle=to_string(rand());
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"exp(")){
        int left=expression.find("exp(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }

        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);
        string previous = expression.substr(left + 4,right-left-4);

        string middle=to_string(exp(stod(previous)));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"sin(")){
        int left=expression.find("sin(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous = expression.substr(left + 4,right-left - 4);
        string middle=to_string(sin(stod(solve(previous))));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"cos(")){
        int left=expression.find("cos(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous = expression.substr(left + 4,right-left - 4);
        string middle=to_string(cos(stod(solve(previous))));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"tan(")){
        int left=expression.find("tan(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous = expression.substr(left + 4,right-left - 4);
        string middle=to_string(tan(stod(solve(previous))));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"ceil(")){
        int left=expression.find("ceil(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }

        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);
        string previous1 = expression.substr(left + 5,right-left-5);

        string middle=to_string(ceil(stod(previous1)));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"floor(")){
        int left=expression.find("floor(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }

        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);
        string previous1 = expression.substr(left + 6,right-left-6);

        string middle=to_string(floor(stod(previous1)));
        expression=before+middle+after;
    }
    while (containsCertainMathFunctions(expression,"log(")){
        int left=expression.find("log(");
        int right=left;
        for (int i = left; i < expression.length(); i++) {
            if (expression[i] == ')') {
                right = i;
                break;
            }
        }
        string before = expression.substr(0, left);
        string after = expression.substr(right + 1);

        string previous = expression.substr(left + 4,right-left - 4);
        string middle=to_string(log(stod(previous)));
        expression=before+middle+after;
    }
    return expression;
}

bool isSingleAnnotation(string expression){
    if(expression.length()<2){
        return false;
    }
    return expression[0]=='/'&&expression[1]=='/';
}

bool isMutipleAnnotationStart(string expression){
    if(expression.length()<2){
        return false;
    }
    return expression[0]=='/'&&expression[1]=='*';
}

bool isMutipleAnnotationEnd(string expression){
    if(expression.length()<2){
        return false;
    }
    return expression[expression.length()-2]=='*'&&expression[expression.length()-1]=='/';
}

void printHelpEnglish(){
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"This is the instruction to the calculator user."<<endl;
    cout<<"Author: YeeTone Wang"<<endl;
    cout<<"Version: 1.06"<<endl;
    cout<<"The author firstly shows his gratitude to the blog of ACBingo."<<endl;
    cout<<"This calculation is based on the library of \"CWTNumber.h\""<<endl;
    cout<<"The original link: https://www.cnblogs.com/acbingo/p/4116206.html"<<endl;
    cout<<endl;
    cout<<"0. The constant value in this calculator:"<<endl;
    cout<<"E=2.718281828459"<<endl;
    cout<<"PI=3.1415926535898"<<endl;
    cout<<endl;
    cout<<"Supported functions:"<<endl;
    cout<<"1. Basic mathematical calculation: + - * /"<<endl;
    cout<<"example-1.1:"<<endl;
    cout<<"3*4"<<endl;
    cout<<"12"<<endl;
    cout<<"example-1.2:"<<endl;
    cout<<"3.45*4.32"<<endl;
    cout<<"14.904"<<endl;
    cout<<endl;

    cout<<"2. calculation with brackets: ( )"<<endl;
    cout<<"example-2.1:"<<endl;
    cout<<"(2+5)*9.9"<<endl;
    cout<<"69.3"<<endl;
    cout<<"example-2.2:"<<endl;\
    cout<<"(4.5+6.8)*1.2"<<endl;
    cout<<"13.56"<<endl;
    cout<<endl;

    cout<<"3. Definition with single char variable: x, y, z"<<endl;
    cout<<"example-3.1:"<<endl;
    cout<<"x=3"<<endl;
    cout<<"y=6"<<endl;
    cout<<"x+2*y"<<endl;
    cout<<"21"<<endl;
    cout<<"example-3.2:"<<endl;
    cout<<"x=1"<<endl;
    cout<<"y=x*2"<<endl;
    cout<<"x=3"<<endl;
    cout<<"x+x*y"<<endl;
    cout<<"9"<<endl;
    cout<<endl;

    cout<<"4. Some single math functions:"<<endl;
    cout<<"example-4.1:"<<endl;
    cout<<"sqrt(3)"<<endl;
    cout<<"1.732051"<<endl;
    cout<<"example-4.2:"<<endl;
    cout<<"pow(2.4,3)"<<endl;
    cout<<"13.824000"<<endl;
    cout<<"Due to time limit, only several functions are supported:"<<endl;
    cout<<"sqrt(a), pow(a,b), max(a,b), abs(a), exp(a),\n"
          "min(a,b), random(), sin(x), cos(x), tan(x), ceil(x), floor(x), log(x)"<<endl;
    cout<<"However, the compound calculation is not supported."<<endl;
    cout<<"If input a compound calculation, the calculator will exist."<<endl;
    cout<<"such as: pow(pow(2,3),4)"<<endl;
    cout<<"No zuo No die why you try?"<<endl;
    cout<<endl;

    cout<<"5. Arbitrary Precision:"<<endl;
    cout<<"Any length of integer or decimal value are supported in this calculator."<<endl;
    cout<<"example-5.1:"<<endl;
    cout<<"5.44444444444444444444444444444444444444444*2+1.1111111111111111111111111111111111111"<<endl;
    cout<<"11.99999999999999999999999999999999999998888"<<endl;
    cout<<"example-5.2:"<<endl;
    cout<<"10.8888888888888888888888888888888888888888888888888888888/2"<<endl;
    cout<<"5.4444444444444444444444444444444444444444444444444444444"<<endl;
    cout<<endl;

    cout<<"6. Add Single line annotation or multiple line annotations:"<<endl;
    cout<<"single line: start with // "<<endl;
    cout<<"multiple lines: start with /*, end with */"<<endl;
    cout<<"The input in the annotation will not be detected by the calculator"<<endl;
    cout<<endl;

    cout<<"This calculator is still being improved. Due to time limit, the calculator supports these functions."<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
}
void printWelcomeEnglish(){
    cout<<"-------------------------------------"<<endl;
    cout<<"Welcome using this simple calculator!"<<endl;
    cout<<"This calculator is mainly for the Assignment2 in CS205(C/C++) course."<<endl;
    cout<<"This calculator is much better than that in Assignment1!"<<endl;
    cout<<"Course Instructor: Shiqi Yu"<<endl;
    cout<<"Author: YeeTone Wang"<<endl;
    cout<<"Version: 1.06"<<endl;
    cout<<"If you need help, please print help to get some information."<<endl;
    cout<<"If you need welcome, please print welcome to get this information again."<<endl;
    cout<<"If you need exit, please print exit to get exit information."<<endl;
    cout<<"如果需要显示中文，请输入Chinese"<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"Please enjoy your calculation!"<<endl;
}

void printHelpChinese(){
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"这是对于计算器用户的使用说明"<<endl;
    cout<<"作者：王奕童"<<endl;
    cout<<"版本：1.06"<<endl;
    cout<<"作者首先很感谢ACBingo的一篇博客"<<endl;
    cout<<"这个计算器是基于\"CWTNumber.h\"头文件实现的"<<endl;
    cout<<"原链接：https://www.cnblogs.com/acbingo/p/4116206.html"<<endl;
    cout<<endl;
    cout<<"0.计算器中的一些常数:"<<endl;
    cout<<"E=2.718281828459"<<endl;
    cout<<"PI=3.1415926535898"<<endl;
    cout<<endl;
    cout<<"计算器中支持的功能"<<endl;
    cout<<"1.基本数学运算：+ - * /"<<endl;
    cout<<"示例-1.1:"<<endl;
    cout<<"3*4"<<endl;
    cout<<"12"<<endl;
    cout<<"示例-1.2:"<<endl;
    cout<<"3.45*4.32"<<endl;
    cout<<"14.904"<<endl;
    cout<<endl;

    cout<<"2.带括号的运算：( )"<<endl;
    cout<<"示例-2.1:"<<endl;
    cout<<"(2+5)*9.9"<<endl;
    cout<<"69.3"<<endl;
    cout<<"示例-2.2:"<<endl;\
    cout<<"(4.5+6.8)*1.2"<<endl;
    cout<<"13.56"<<endl;
    cout<<endl;

    cout<<"3.单个字符的自变量: x, y, z"<<endl;
    cout<<"示例-3.1:"<<endl;
    cout<<"x=3"<<endl;
    cout<<"y=6"<<endl;
    cout<<"x+2*y"<<endl;
    cout<<"15"<<endl;
    cout<<"示例-3.2:"<<endl;
    cout<<"x=1"<<endl;
    cout<<"y=x*2"<<endl;
    cout<<"x=3"<<endl;
    cout<<"x+x*y"<<endl;
    cout<<"9"<<endl;
    cout<<endl;

    cout<<"4.一些简单的数学函数:"<<endl;
    cout<<"示例-4.1:"<<endl;
    cout<<"sqrt(3)"<<endl;
    cout<<"1.732051"<<endl;
    cout<<"示例-4.2:"<<endl;
    cout<<"pow(2.4,3)"<<endl;
    cout<<"13.824000"<<endl;
    cout<<"由于时间的限制，现只支持一下数学函数："<<endl;
    cout<<"sqrt(a), pow(a,b), max(a,b), abs(a), exp(a),\n"
          "min(a,b), random(), sin(x), cos(x), tan(x), ceil(x), floor(x), log(x)"<<endl;
    cout<<"该计算器尚未完全支持复合数学函数的运算"<<endl;
    cout<<"如果输入复合数学函数的运算，则该计算器有可能异常退出"<<endl;
    cout<<"例如：pow(pow(2,3),4)"<<endl;
    cout<<"No zuo No die why you try?"<<endl;
    cout<<endl;

    cout<<"5.高精度运算："<<endl;
    cout<<"该计算器支持任意长度的浮点数运算"<<endl;
    cout<<"示例-5.1:"<<endl;
    cout<<"5.44444444444444444444444444444444444444444*2+1.1111111111111111111111111111111111111"<<endl;
    cout<<"11.99999999999999999999999999999999999998888"<<endl;
    cout<<"示例-5.2:"<<endl;
    cout<<"10.8888888888888888888888888888888888888888888888888888888/2"<<endl;
    cout<<"5.4444444444444444444444444444444444444444444444444444444"<<endl;
    cout<<endl;

    cout<<"6.单行注释、多行注释实现"<<endl;
    cout<<"单行注释：某一行以//开始 "<<endl;
    cout<<"多行注释：以/*开始，以*/结束"<<endl;
    cout<<"注释内的内容不会被计算器所识别"<<endl;
    cout<<endl;

    cout<<"该计算器仍然处于改进当中。由于时间的限制，现暂时只支持这么多功能。"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
}

void printWelcomeChinese(){
    cout<<"-------------------------------------"<<endl;
    cout<<"欢迎使用本计算器！"<<endl;
    cout<<"本计算器主要是用于南方科技大学CS205(C/C++程序设计)课程的第二次作业。"<<endl;
    cout<<"本计算器实现的功能比第一次作业要强大很多！"<<endl;
    cout<<"课程教师：于仕琪"<<endl;
    cout<<"作者：王奕童"<<endl;
    cout<<"版本号：1.06"<<endl;
    cout<<"如果需要帮助，则请在屏幕上输入help"<<endl;
    cout<<"如果需要欢迎，则请在屏幕上输入welcome"<<endl;
    cout<<"如果需要退出，则请在屏幕上输入exit"<<endl;
    cout<<"If you need to show in English, please print English"<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"开始运算吧！"<<endl;
}