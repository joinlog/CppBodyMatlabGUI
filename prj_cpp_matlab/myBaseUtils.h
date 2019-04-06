/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myBaseUtils.h
 * Author: join
 *
 * Created on 2019年4月6日, 上午6:55
 */

#ifndef MYBASEUTILS_H
#define MYBASEUTILS_H
#include "cstdlib"

class myBaseUtils
{
public:
    myBaseUtils();
    myBaseUtils(const myBaseUtils& orig);
    virtual ~myBaseUtils();
    //取minval-maxval中间的随机数，包含minval，不包含maxval; 如果返回的四maxval，表示计算无效
    static int rand(int minval, int maxval);
    static float rand(float minval, float maxval);
    static int cutValue(int val, int maxVal, int minVal);
private:

};

#endif /* MYBASEUTILS_H */

