
#include "IDataChangeListener.h"

IDataChangeListener::IDataChangeListener(std::string matScriptName, std::string matVarName) : mtScriptName(matScriptName)
{
    m_eng = myMatlabEngine::getInstance();
    if (!m_eng)
    {
        throw "myMatlabEngine::getInstance fail";
    }
    mtVal.SetEngine(m_eng->GetEngine());
    mtVal.SetVarName(matVarName);
}

IDataChangeListener::~IDataChangeListener()
{
}

void IDataChangeListener::onDataChanging(const Eigen::MatrixXf &val)
{
    // 更新mtVal，并发送到matlab引擎
    mtVal.put(val);

    // 调用matlab引擎画出mStatistic
    m_eng->exec(mtScriptName);
    //std::cout << mtScriptName << std::endl;
}
