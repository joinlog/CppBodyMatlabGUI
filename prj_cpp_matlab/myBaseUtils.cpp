/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myBaseUtils.cpp
 * Author: join
 * 
 * Created on 2019年4月6日, 上午6:55
 */

#include <climits>

#include "myBaseUtils.h"

myBaseUtils::myBaseUtils()
{
}

myBaseUtils::myBaseUtils(const myBaseUtils& orig)
{
}

myBaseUtils::~myBaseUtils()
{
}

int myBaseUtils::myRand(int minval, int maxval)
{
    if (minval >= maxval)
    {
        return maxval;
    }

    return minval + rand() % (maxval - maxval);
}

float myBaseUtils::myRand(float minval, float maxval)
{
    return minval + (float)rand() * (maxval - minval) / (float)RAND_MAX;
}

int myBaseUtils::cutValue(int val, int maxVal, int minVal)
{
    if (val < minVal)
    {
        return minVal;
    }
    else if (val > maxVal)
    {
        return maxVal;
    }

    return val;
}