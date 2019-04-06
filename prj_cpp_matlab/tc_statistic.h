#pragma once

#include "main.h"
#include "matlabWrapper.h"
#include "CellWrapper.h"

//配置定义


class TcStatistic {
public:
    TcStatistic();
    ~TcStatistic();
    
    
    void SetUpGlobalParamWithMatlab();

    //更新并画Agv框
    void UpdateStatistic();

private:
    void SetUpMatlabEngine();
    
    void InitCellWrapper();
    void GetCellWrapperParam(int &mi, int &mj, int &mradius, int &mcellNum, int &mminNodeNum, int &mmaxNodeNum);
    void EigenMat2CellWrapperParam(EigenMat &em, int &mi, int &mj, int &mradius, int &mcellNum, int &mminNodeNum, int &mmaxNodeNum);
    void GetRateRange(RateStatus_t &minRate, RateStatus_t &maxRate);
    void EigenMat2RateRange(EigenMat &em, int row, RateStatus_t &rs);
    
private:
    myMatlabEngine *m_eng;
    // 从matlab脚本读入数据初始化CellWrapper
//    int imax;
//    int jmax;
//    int radius;
//    int cellNum; // 生成umpCells的个数
//    int minNodeNum; //每个Cell中最小节点个数
//    int maxNodeNum; //每个Cell中最大节点个数
    MatIOArray mMAInputParam; // 1行6列
//    RateStatus_t minRate; // 各个状态占有最大比率,用于初始化cell
//    RateStatus_t maxRate; // 各个状态占有最大比率,用于初始化cell
    MatIOArray mMARateRange; // 2行4列；
    // 输出统计数据 
    // i,j,s,e,i,r  n*6 n行6列 即
    MatIOArray mMAStatistic;
    Eigen::MatrixXf mStatistic;
    CellWrapper mCellWrapper;
};

