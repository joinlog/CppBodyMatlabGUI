#include "VPlot.h"


VPlot::VPlot(std::string matScriptName, std::string matVarName)
{
    ml = new IDataChangeListener(matScriptName, matVarName);
    if (!ml)
    {
        throw "VPlot Construct fail for new IDataChangeListener";
    }

    
}


VPlot::~VPlot()
{
    if (!ml)
    {
        delete ml;
        ml = nullptr;
    }
}

void VPlot::registerListenner(IDataChangeListener *l)
{

}

void VPlot::removeListenner(IDataChangeListener *l)
{

}

void VPlot::notify()
{
    if (ml != nullptr)
    {
        ml->onDataChanging(mVal);
    }
}


void VPlot::request()
{
    if (ml != nullptr)
    {
        ml->onRequestData(mVal);
    }
}

const Eigen::MatrixXf & VPlot::GetVal()
{
    request();
    return mVal;
}


void VPlot::SetVal(Eigen::MatrixXf &val)
{
    mVal = val;
    // 每一个设置都有默认带一个notify
    notify();
}
