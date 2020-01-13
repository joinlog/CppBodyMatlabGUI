// cm_demo1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <fstream>

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
		bIsStepByStep = atoi(argv[3]) == 0 ? false : true;
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


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
