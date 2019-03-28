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
    // x,y,hl,hw,degree  n*5 n行5列
    mMAStatistic.SetEngine(m_eng->GetEngine());
    mMAStatistic.SetVarName("mBoxes");

}

void TcStatistic::SetStatisticSize(int r, int c)
{
    mStatistic.resize(r, c);
}

void TcStatistic::UpdateStatistic()
{
    // 更新mStatistic
    
    // 更新mMAStatistic，并发送到matlab引擎
    mMAStatistic.put(mStatistic);
     std::cout << "mStatistic is" << std::endl << mStatistic << std::endl;
     
     // 调用matlab引擎画出mStatistic
     m_eng->exec("drawBoxes");    
}
