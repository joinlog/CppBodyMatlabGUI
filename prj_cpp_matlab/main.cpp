/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: 
 *
 * Created on 2018年12月11日, 下午4:30
 */
#include "main.h"

#include "Algo_Assistant.h"
#include "tc_statistic.h"

using namespace std;

#define    ENABLE_MATLAB_GUI   true

int main(int argc, char** argv) 
{
#if ENABLE_MATLAB_GUI
    TcStatistic tcm;    
    tcm.SetUpMatlabEngine();
    tcm.SetUpGlobalParamWithMatlab();

    system("pwd");
#endif
    
    int mRow = 100;
    int mCol = 100;
    bool bIsStepByStep = false;
    if (argc == 4)
    {
        mRow = atoi(argv[1]);
        mCol = atoi(argv[2]);
        bIsStepByStep = atoi(argv[2]) == 0 ? false : true;
    }
    else
    {
        cout << "Usage:" << argv[0] << " row col isStepbyStep" << endl;
    }
    cout << "row=" << mRow << ",col=" << mCol << endl;
    tcm.SetStatisticSize(mRow, mCol);
    
    do 
    {
#if ENABLE_MATLAB_GUI
        tcm.UpdateStatistic();
#endif

        if (!bIsStepByStep)
        {
            Sleep(1000);
        }
        else
        {
            std::cout << "Press q to quit. Press Any other Key to Continue..." << std::endl;
            char mcret = getchar();
            if (mcret == 'q')
            {
                break;
            }     
        }
    } while (true);
    
    printf("statistic finished!\n");
    return 0;
}
