#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;

static inline bool isDigit(string s);
static inline void bigIntegerMultiply(string big1,string big2);
static inline string clearBeforeZero(string numStr);

int main()
{
    cout<<"Please input two integers"<<endl;
    string numA,numB;
    cin >> numA;

    bool aNegative=numA[0]=='-';
    if(aNegative){
        numA=numA.substr(1);
    }
    numA=clearBeforeZero(numA);
    if(!isDigit(numA)){
        cerr << "The first input is not correct. Exit..." <<endl;
        return 0;
    }

    cin >> numB;
    bool bNegative=numB[0]=='-';
    if(bNegative){
        numB=numB.substr(1);
    }
    numB=clearBeforeZero(numB);
    if(!isDigit(numB)){
        cerr << "The second input is not correct. Exit..." <<endl;
        return 0;
    }

    if(aNegative^bNegative){
        cout<<"-";
    }
    cout<<bigIntegerMultiply(numA,numB)<<endl;

    return 0;
}
bool isDigit(string s)
{
    for (int i = 0; i < s.length(); ++i) {
        if(!isdigit(s[i])){ //The function to check if a char can be transformed into a digital number.
            return false;
        }
    }
    return true;
}

string clearBeforeZero(string numStr)
{
    int noneZero=0;
    for (int i = 0; i < numStr.length(); ++i) {
        if(numStr[i]!='0'){
            noneZero=i;
            break;
        }
    }
    return numStr.substr(noneZero);
}

string bigIntegerMultiply(string big1,string big2)
{
    string result;
    int intArray1[big1.length()],intArray2[big2.length()];
    for (int i = 0; i < big1.length(); ++i) {
        intArray1[i]=big1[i]-'0';
    }
    for (int i = 0; i < big2.length(); ++i) {
        intArray2[i]=big2[i]-'0';
    }
    int resultArray[big1.length()+big2.length()];
    memset(resultArray,0, sizeof(resultArray));
    for (int i = big1.length()-1; i >= 0; --i) {
        for (int j = big2.length()-1; j >= 0; --j) {
            resultArray[i+j]+=intArray1[i]*intArray2[j];
        }
    }

    for (int k = big1.length()+big2.length()-1; k > 0; --k) {
        int upper=resultArray[k]/10;
        resultArray[k]=resultArray[k]%10;
        resultArray[k-1]+=upper;
    }
    bool isZero= true;
    for (int l = 0; l < big1.length()+big2.length()-1; ++l) {
        if(resultArray[l]!=0){
            isZero= false;
        }
        if(!isZero){
            result+=resultArray[l];
        }
    }
    if(isZero){
        result="0";
    }
    return result;
}
