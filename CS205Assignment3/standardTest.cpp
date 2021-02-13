/*
#include <iostream>
#include <chrono>

using namespace std;

unsigned long long xp,yp,zp;


static unsigned int vectorSize=0;
static float *vector1= nullptr;
static float *vector2= nullptr;
static double result= 0;

int main();
float randomGenerate();
void cinSize();
void initiate();
void cinElements(int signNumber);
void singleThreadSum();

int main(){
    cinSize();
    initiate();
    long t0=clock();
    cinElements(1);
    cinElements(2);
    long tc=clock();
    cout<<"Data IO Time:"<<(tc-t0)<<"ms"<<endl;
    singleThreadSum();
}
float randomGenerate(){
    xp^=xp<<3;
    xp^=xp>>7;
    xp^=xp<<1;
    unsigned long long t=xp;
    xp=yp;
    yp=zp;
    zp=t^xp^yp;
    return zp/INT16_MAX;
}

void cinSize(){
    cin>>vectorSize;
}

void initiate(){
    srand((unsigned int)time(nullptr));
    xp=rand();
    yp=rand();
    zp=rand();
    free(vector1);
    free(vector2);
    vector1=new float[vectorSize];
    vector2=new float[vectorSize];
}

void cinElements(int signNumber){
    if(signNumber==1){
        for (int i = 0; i < vectorSize; ++i) {
            vector1[i]=randomGenerate();
        }
    }else{
        for (int i = 0; i < vectorSize; ++i) {
            vector2[i]=randomGenerate();
        }
    }
}

void singleThreadSum(){
    long t1=clock();
    for (int i = 0; i < vectorSize; ++i) {
        result+=vector1[i]*vector2[i];
    }
    cout<<result<<endl;
    long t2=clock();
    cout<<(t2-t1)<<"ms"<<endl;
}
*/
