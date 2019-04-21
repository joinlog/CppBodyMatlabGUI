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
#include <windows.h>
#include "main.h"

#include "tc_statistic.h"

using namespace std;

#define    ENABLE_MATLAB_GUI   true

int main(int argc, char** argv) 
{
#if ENABLE_MATLAB_GUI
    TcStatistic tcm;    
    
    tcm.SetUpGlobalParamWithMatlab();

    system("pwd");
    std::cout << std::endl;
    std::cout << "Press q to quit. Press Any other Key to Continue..." << std::endl;
    char mcret = getchar();
#endif

    bool bIsStepByStep = false;
    if (argc == 2)
    {
        bIsStepByStep = atoi(argv[1]) == 0 ? false : true;
    }
    else
    {
        cout << "Usage:" << argv[0] << " isStepbyStep" << endl;
    }

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
