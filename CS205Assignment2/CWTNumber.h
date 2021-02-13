//
// Created by 16011 on 2020/9/24.
//

#ifndef CPPLEARN_CWTNUMBER_H
#define CPPLEARN_CWTNUMBER_H

#endif //CPPLEARN_CWTNUMBER_H

// WTNumber.h: interface for the CWTNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTNUMBER_H__92E62B40_491A_4A75_AB89_FFB160DB2343__INCLUDED_)
#define AFX_WTNUMBER_H__92E62B40_491A_4A75_AB89_FFB160DB2343__INCLUDED_

#if _MSC_VER > 1000
/////#pragma once
#endif // _MSC_VER > 1000

#define INT_BIT_MAX 255
#define FLOAT_BIT_MAX 255

class CWTNumber
{
private:
    int intbits;                     /* 整数数位*/
    int floatbits;                   /* 小数有效数位*/
    char infinite;                   /* 无穷大*/
    char sign;                       /* 符号*/
    char intpart[INT_BIT_MAX];       /* 整数部分*/
    char floatpart[FLOAT_BIT_MAX];   /* 小数部分*/
private:
    char* m_sz;
public:
    /* 算术函数指针类型.*/
    typedef void (*PFNCALC)(const CWTNumber&,const CWTNumber&,CWTNumber&);
    CWTNumber();
    CWTNumber(const char* szNum);
    ~CWTNumber();
    /* 转换成字符串*/
    char* toString();
    void FreeString();
    /* 初始化WTNumber为0.*/
    void InitWTNumberToZero();
    /* 判断需要多少个字符空间存储WTNumber转换的字符串.*/
    int StrLenByWTNumber();
    /* 从字符串转换到WTNumber.*/
    void StrToWTNumber(const char *arr);
    /* 从WTNumber转换到字符串.*/
    void WTNumberToStr(char *szBuf);
    /* 调节数位,删除最高整数位是0的和最低小数位是0的数位.*/
    void AdjustBits();
    /* 移动小数点,delta=0不移动,delta<0往左移动,delta>0往右移动.*/
    void MoveFloatPoint(int delta);
    /* 使无穷大 */
    void MakeInfinite();
    /* 比较2个数大小 */
    int WTCompare(const CWTNumber& n) const;
    /* 判断是否为0 */
    int IsZero() const;
    /* 赋值号重载*/
    CWTNumber& operator=(const CWTNumber& n);

    /* 运算符重载 */
    CWTNumber operator+(const CWTNumber& n);
    CWTNumber operator-(const CWTNumber& n);
    CWTNumber operator*(const CWTNumber& n);
    CWTNumber operator/(const CWTNumber& n);
    CWTNumber& operator+=(const CWTNumber& n);
    CWTNumber& operator-=(const CWTNumber& n);
    CWTNumber& operator*=(const CWTNumber& n);
    CWTNumber& operator/=(const CWTNumber& n);

    bool operator>(const CWTNumber& n);
    bool operator>=(const CWTNumber& n);
    bool operator<(const CWTNumber& n);
    bool operator<=(const CWTNumber& n);
    bool operator==(const CWTNumber& n);
    bool operator!=(const CWTNumber& n);
    /* 加法*/
    static void WTAdd(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* 乘法*/
    static void WTMultiply(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* 减法*/
    static void WTSubtract(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* 除法*/
    static void WTDivide(const CWTNumber& n1,const CWTNumber& n2,CWTNumber& Res);
    /* 根据算术函数返回结果 */
    static char *Result(const char *val1,const char *val2,PFNCALC pfnCalc);
};


#endif // !defined(AFX_WTNUMBER_H__92E62B40_491A_4A75_AB89_FFB160DB2343__INCLUDED_)