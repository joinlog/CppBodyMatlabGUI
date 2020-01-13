﻿// cmdemo2.cpp: 定义控制台应用程序的入口点。
//
#include <windows.h>
#include "IDataChangeNotifier.h"
#include "DrawBoxes.h"

int main()
{
    IDataChangeListener mBoxes("drawBoxes", "mBoxes");
    DrawBoxes mDrawBoxes;
    mDrawBoxes.registerListenner(&mBoxes);

    const float g_try_code = 6114121; //try = 116114121
    const float g_clm_code = 9108109; //clm = 99108109

    std::vector<float> mBoxParam;// = { 100, 200, 8.5, 2, 90 };
    int mCnt = 100;
    while (--mCnt)
    {

        mBoxParam.push_back(g_clm_code);
        mBoxParam.push_back(0);
        mBoxParam.push_back(0);
        mBoxParam.push_back(0);
        mBoxParam.push_back(0);
        for (int i = 0; i < 1; ++i)
        {
            mBoxParam.push_back(100);
            mBoxParam.push_back(200);
            mBoxParam.push_back(8.5);
            mBoxParam.push_back(2);
            mBoxParam.push_back(90 + mCnt);

        }
        mBoxParam.push_back(g_try_code);
        mBoxParam.push_back(0);
        mBoxParam.push_back(0);
        mBoxParam.push_back(0);
        mBoxParam.push_back(0);

        mDrawBoxes.SetBoxes(mBoxParam);
        mDrawBoxes.notify();
        Sleep(800);
        std::cout << ".";
    }
    return 0;
}

