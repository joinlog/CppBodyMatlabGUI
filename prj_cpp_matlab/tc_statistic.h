#pragma once

#include "main.h"
#include "matlabWrapper.h"

//配置定义


class TcStatistic {
public:
    TcStatistic();
    ~TcStatistic();
    
    void SetUpMatlabEngine();
    void SetUpGlobalParamWithMatlab();
    void SetStatisticSize(int r, int c);
    
    //更新并画Agv框
    void UpdateStatistic();

private:

private:
    myMatlabEngine *m_eng;

    // x_s,y_s,x_e,x_e  n*4 n行4列
    MatIOArray mMAStatistic;
    Eigen::MatrixXf mStatistic;
    
};

