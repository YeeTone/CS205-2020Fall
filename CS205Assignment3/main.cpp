#pragma GCC optimize(3,"Ofast","inline")
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>
#include <ctime>

#define Thread_Number std::thread::hardware_concurrency()

using namespace std;

unsigned long long xp,yp,zp;

static unsigned int vectorSize=0;
static float *vector1= nullptr;
static float *vector2= nullptr;
static double results[8];
static double result;
static bool isRandom = false;

int main();/**/
inline float randomGenerate();/**/
inline void improveCIO();/**/
inline void cinSize();/**/
void checkIsUserRandom();/**/
inline bool checkSizeLength(const string& sizeStr);/**/
inline bool checkSizeMaterial(const string& sizeStr);/**/
void initiate();/**/
inline void cinElements(int signNumber);/**/
inline bool checkElementMaterial(const string& elementStr);/**/
inline void singleThreadSum();/**/
inline void multiplyThreadSum();/**/
inline void subMultiply(const int& start,const int& end,const int& sign);/**/

int main(){
    improveCIO();
    string check="Y";
    while(check=="Y"){
        cinSize();
        checkIsUserRandom();
        initiate();
        long t0=clock();
        cinElements(1);
        cinElements(2);
        long tc=clock();
        cout<<"Data IO Time:"<<(tc-t0)<<"ms"<<endl;
        singleThreadSum();
        result=0;
        multiplyThreadSum();
        cout<<"Do you want to continue calculating? Print[Y] to continue."<<endl;
        cin>>check;
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
    return zp/INT16_MAX;
}
inline void improveCIO(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.setf(ios::fixed,ios::floatfield);
}
inline void cinSize(){
    cout<<"Please input the size:"<<endl;
    while (true){
        string sizeStr;
        cin>>sizeStr;
        if(checkSizeMaterial(sizeStr)){
            if(!checkSizeLength(sizeStr)){
                cout<<"The size is too big! Out of memory!"<<endl;
            }else{
                vectorSize=stoi(sizeStr);
                break;
            }
        }
        cout<<"The input is not correct. Please input the size again:"<<endl;
    }
}
void checkIsUserRandom(){
    cout<<"If you want to be a random test? If so, please print[Y]."<<endl;
    string input;
    cin>>input;
    isRandom=(input=="Y");
}
bool checkSizeLength(const string& sizeStr){
    return sizeStr.length()<10;
}
bool checkSizeMaterial(const string& sizeStr){
    return all_of(sizeStr.begin(),sizeStr.end(),::isdigit);
}
void initiate(){
    srand((unsigned int)time(nullptr));
    xp=rand();
    yp=rand();
    zp=rand();
    delete [] vector1;
    delete [] vector2;
    vector1=new float[vectorSize];
    vector2=new float[vectorSize];
}
inline void cinElements(int signNumber){
    if(isRandom){
        if(signNumber==1){
            for (int i = 0; i < vectorSize; ++i) {
                //cin>>vector1[i];
                /*vector1[i]=randomGenerate();*/
                vector1[i]=2;
            }
        }else{
            for (int i = 0; i < vectorSize; ++i) {
                //cin>>vector2[i];
                /*vector2[i]=randomGenerate();*/
                vector2[i]=2;
            }
        }
    }else{
        if(signNumber==1){
            string input;
            for (int i = 0; i < vectorSize; ++i) {
                cout<<"Please input vector1["<<i<<"]:"<<endl;
                while(true){
                    cin>>input;
                    if(checkElementMaterial(input)){
                        vector1[i]=stof(input);
                        break;
                    }else{
                        cout<<"The input is incorrect! Please input again:"<<endl;
                    }
                }
            }
        } else{
            string input;
            for (int i = 0; i < vectorSize; ++i) {
                cout<<"Please input vector2["<<i<<"]:"<<endl;
                while(true){
                    cin>>input;
                    if(checkElementMaterial(input)){
                        vector2[i]=stof(input);
                        break;
                    }else{
                        cout<<"The input is incorrect! Please input again:"<<endl;
                    }
                }
            }
        }
    }

}
inline bool checkElementMaterial(const string& elementStr){
    bool hasDot= false;
    for (int i = 0; i < elementStr.length(); ++i) {
        char e=elementStr[i];
        if(i==0&&e=='-'){
            continue;
        }
        else if(!isdigit(e)){
            if(e=='.'){
                if(hasDot){
                    return false;
                }else{
                    hasDot=true;
                }
            }else{
                return false;
            }
        }
    }
    return true;
}
inline void singleThreadSum(){
    long t1=clock();
    for (int i = 0; i < vectorSize; ++i) {
        result+=vector1[i]*vector2[i];
    }
    cout<<result<<endl;
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
}
inline void multiplyThreadSum(){
    long t3=clock();
    unsigned int each=vectorSize/Thread_Number;
    unsigned int start=0,end=each;
    vector<thread>threadPool;
    threadPool.reserve(Thread_Number);
    for (int i = 0; i < Thread_Number; ++i) {
        if(i==Thread_Number-1){
            end=vectorSize;
        }
        threadPool.emplace_back(subMultiply,start,end,i);
        start=end;
        end+=each;
    }
    for (int i=0;i<Thread_Number; ++i){
        threadPool[i].join();
    }
    double r=0;
    for (int i = 0; i < Thread_Number; ++i) {
        r+=results[i];
    }
    cout<<r<<endl;
    long t4=clock();
    cout<<(t4-t3)<<"ms"<<endl;
}
inline void subMultiply(const int& start,const int& end,const int& sign){
    double re=0;
    for (int i = start; i < end; ++i) {
        re+=vector1[i]*vector2[i];
    }
    results[sign]=re;
}