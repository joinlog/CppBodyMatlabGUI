#include <Eigen/Eigen>
#include "tc_statistic.h"
#include "matlabWrapper.h"

TcStatistic::TcStatistic()
{
    m_eng = new myMatlabEngine();
}

TcStatistic::~TcStatistic()
{
    delete m_eng;
    m_eng = NULL;
}

void TcStatistic::SetUpMatlabEngine()
{
    
    char *mCwd = getcwd(NULL, 0);

    //将matlab引擎目录指定到当前程序运行目录，使可以调用其中的matlab scirpt 文件
    std::string strCmd = "cd ";
    strCmd.append(mCwd);
    std::cout << strCmd << std::endl;
    m_eng->exec(strCmd);
    free(mCwd);
    mCwd = NULL;

    m_eng->exec("main");
}

void TcStatistic::SetUpGlobalParamWithMatlab()
{
    SetUpMatlabEngine();
    
    mMAInputParam.SetEngine(m_eng->GetEngine());
    mMAInputParam.SetVarName("CellsParam");
    
    mMARateRange.SetEngine(m_eng->GetEngine());
    mMARateRange.SetVarName("RateRange");
    
    // x,y,hl,hw,degree  n*5 n行5列
    mMAStatistic.SetEngine(m_eng->GetEngine());
    mMAStatistic.SetVarName("mBoxes");

}

void TcStatistic::UpdateStatistic()
{
    // 更新mStatistic
    mCellWrapper.UpdateCells();
    // 将更新后的Cells的内容更新到mStatistic
    // TODO
    mCellWrapper.Cells2EgineMat(mStatistic);
    
    // 更新mMAStatistic，并发送到matlab引擎
    mMAStatistic.put(mStatistic);
     std::cout << "mStatistic is" << std::endl << mStatistic << std::endl;
     
     // 调用matlab引擎画出mStatistic
     m_eng->exec("drawBoxes");    
}

void TcStatistic::InitCellWrapper()
{
    int mi;
    int mj;
    int mradius;
    int mcellNum; 
    int mminNodeNum;
    int mmaxNodeNum;
    GetCellWrapperParam(mi, mj, mradius, mcellNum, mminNodeNum, mmaxNodeNum);
    
    RateStatus_t minRate;
    RateStatus_t maxRate;
    GetRateRange(minRate, maxRate);
    mCellWrapper.InitCellWrapper(mi, mj, mradius, mcellNum, mminNodeNum, mmaxNodeNum, minRate, maxRate);
    
    mCellWrapper.InitCells();
}

void TcStatistic::GetCellWrapperParam(int& mi, int& mj, int& mradius, int& mcellNum, int& mminNodeNum, int& mmaxNodeNum)
{
    EigenMat mInputParam;
    mMAInputParam.get(mInputParam);
    EigenMat2CellWrapperParam(mInputParam, mi, mj, mradius, mcellNum, mminNodeNum, mmaxNodeNum);
}

void TcStatistic::EigenMat2CellWrapperParam(EigenMat& em, int& mi, int& mj, int& mradius, int& mcellNum, int& mminNodeNum, int& mmaxNodeNum)
{
    mi = em(0, 0);
    mj = em(0, 1);
    mradius = em(0, 2);
    mcellNum = em(0, 3);
    mminNodeNum = em(0, 4);
    mmaxNodeNum = em(0, 5);
    
}

void TcStatistic::GetRateRange(RateStatus_t& minRate, RateStatus_t& maxRate)
{
    EigenMat mRateRange;
    mMARateRange.get(mRateRange);
    EigenMat2RateRange(mRateRange, 0, minRate);
    EigenMat2RateRange(mRateRange, 1, maxRate);
}

void  TcStatistic::EigenMat2RateRange(EigenMat& em, int row, RateStatus_t& rs)
{
    rs.s = em(row, 0);
    rs.e = em(row, 1);
    rs.i = em(row, 2);
    rs.r = em(row, 3);
    
}

