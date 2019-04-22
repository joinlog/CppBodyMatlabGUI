#include <io.h>
#include <Eigen/Eigen>
#include "tc_statistic.h"

TcStatistic::TcStatistic()
{
}

TcStatistic::~TcStatistic()
{
}

void TcStatistic::SetUpMatlabEngine()
{
    
    char *mCwd = getcwd(NULL, 0);

    //将matlab引擎目录指定到当前程序运行目录，使可以调用其中的matlab scirpt 文件
    std::string strCmd = "cd ";
    strCmd.append(mCwd);
    std::cout << strCmd << std::endl;

    free(mCwd);
    mCwd = NULL;
    
}

void TcStatistic::SetUpGlobalParamWithMatlab()
{
    SetUpMatlabEngine();

 //    int imax;
 //    int jmax;
 //    int radius;
 //    int cellNum; // 生成umpCells的个数
 //    int minNodeNum; //每个Cell中最小节点个数
 //    int maxNodeNum; //每个Cell中最大节点个数

    mMAInputParam = Eigen::MatrixXf(1,6);
    mMAInputParam << 100, 100, 7, 500, 6, 6;
        
//    float lambda; // λ
//    float tau; // τ
//    float miu; //μ
//    float sigma; //σ,?
//    float epsilon; // ε
//    float omega;   例如ω= λ / 8

    mMAFuncParam = Eigen::MatrixXf(1,6);
    mMAFuncParam << 0.064, 0.2572, 0.053, 0.3028, 0.3298, 0.064 * 0.125;
    
//    RateStatus_t minRate; // 各个状态占有最大比率,用于初始化cell
//    RateStatus_t maxRate; // 各个状态占有最大比率,用于初始化cell

    mMARateRange = Eigen::MatrixXf(2,4);
    mMARateRange << 0.8, 0, 0.2, 0,
                    0.8, 0, 0.2, 0;

    InitCellWrapper();
}

void TcStatistic::UpdateStatistic()
{
    std::cout << "UpdateStatistic start" << std::endl;
    // 更新mStatistic
    mCellWrapper.UpdateCells();
    std::cout << "After UpdateCells" << std::endl;
     std::cout << "UpdateStatistic end" << std::endl;
}

void TcStatistic::InitCellWrapper()
{
    int mi;
    int mj;
    int mradius;
    int mcellNum; 
    int mminNodeNum;
    int mmaxNodeNum;
    
    float lambda; // λ
    float tau; // τ
    float miu; //μ
    float sigma; //σ,ς
    float epsilon; // ε
    float omega;   //例如ω= λ / 8
    
    GetCellWrapperParam(mi, mj, mradius, mcellNum, mminNodeNum, mmaxNodeNum, lambda, tau, miu, sigma, epsilon, omega);
    
    RateStatus_t minRate;
    RateStatus_t maxRate;
    GetRateRange(minRate, maxRate);
    mCellWrapper.InitCellWrapper(mi, mj, mradius, mcellNum, mminNodeNum, mmaxNodeNum, minRate, maxRate, lambda, tau, miu, sigma, epsilon, omega);
    std::cout << "After InitCellWrapper" << std::endl;
    mCellWrapper.InitCells();
    std::cout << "After InitCells" << std::endl;
}

void TcStatistic::GetCellWrapperParam(int& mi, int& mj, int& mradius, int& mcellNum, int& mminNodeNum, int& mmaxNodeNum,
    float &mlambda, float &mtau, float &mmiu, float &msigma, float &mepsilon, float &omega)
{
    EigenMat2CellWrapperParam(mMAInputParam, mi, mj, mradius, mcellNum, mminNodeNum, mmaxNodeNum);
    
    EigenMat2FuncParam(mMAFuncParam,  mlambda, mtau, mmiu, msigma, mepsilon, omega);
}

void TcStatistic::EigenMat2CellWrapperParam(Eigen::MatrixXf& em, int& mi, int& mj, int& mradius, int& mcellNum, int& mminNodeNum, int& mmaxNodeNum)
{
    mi = em(0, 0);
    mj = em(0, 1);
    mradius = em(0, 2);
    mcellNum = em(0, 3);
    mminNodeNum = em(0, 4);
    mmaxNodeNum = em(0, 5);

    
}

void TcStatistic::EigenMat2FuncParam(Eigen::MatrixXf& em, float &mlambda, float &mtau, float &mmiu, float &msigma, float &mepsilon, float &omega)
{
    mlambda = em(0, 0);
    mtau = em(0, 1);
    mmiu = em(0, 2);
    msigma = em(0, 3);
    mepsilon = em(0, 4);
    omega = em(0, 5);
}

void TcStatistic::GetRateRange(RateStatus_t& minRate, RateStatus_t& maxRate)
{
    EigenMat2RateRange(mMARateRange, 0, minRate);
    EigenMat2RateRange(mMARateRange, 1, maxRate);
}

void  TcStatistic::EigenMat2RateRange(Eigen::MatrixXf& em, int row, RateStatus_t& rs)
{
    rs.s = em(row, 0);
    rs.e = em(row, 1);
    rs.i = em(row, 2);
    rs.r = em(row, 3);
    
}

