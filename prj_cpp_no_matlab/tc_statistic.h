#pragma once

#include "main.h"

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
    void GetCellWrapperParam(int &mi, int &mj, int &mradius, int &mcellNum, int &mminNodeNum, int &mmaxNodeNum,
                float &mlambda, float &mtau, float &mmiu, float &msigma, float &mepsilon, float &omega);
    void EigenMat2CellWrapperParam(Eigen::MatrixXf &em, int &mi, int &mj, int &mradius, int &mcellNum, int &mminNodeNum, int &mmaxNodeNum);
    void EigenMat2FuncParam(Eigen::MatrixXf &em, float &mlambda, float &mtau, float &mmiu, float &msigma, float &mepsilon, float &omega);
    void GetRateRange(RateStatus_t &minRate, RateStatus_t &maxRate);
    void EigenMat2RateRange(Eigen::MatrixXf &em, int row, RateStatus_t &rs);
    
private:

//    int imax;
//    int jmax;
//    int radius;
//    int cellNum; // 生成umpCells的个数
//    int minNodeNum; //每个Cell中最小节点个数
//    int maxNodeNum; //每个Cell中最大节点个数

    Eigen::MatrixXf mMAInputParam; // 1行6列
    //    float lambda; // λ
//    float tau; // τ
//    float miu; //μ
//    float sigma; //σ,ς
//    float epsilon; // ε
    //float omega;   //例如ω= λ / 8
    Eigen::MatrixXf mMAFuncParam;
//    RateStatus_t minRate; // 各个状态占有最大比率,用于初始化cell
//    RateStatus_t maxRate; // 各个状态占有最大比率,用于初始化cell
    Eigen::MatrixXf mMARateRange; // 2行4列；
    // 输出统计数据 

    CellWrapper mCellWrapper;
};
