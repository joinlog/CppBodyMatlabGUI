#pragma once
#include <engine.h>
#include <string>
#include <iostream>
#include <Eigen/Eigen>
#include "matlabWrapper.h"

class IDataChangeListener
{
public:
    IDataChangeListener(std::string matScriptName, std::string matVarName);
    ~IDataChangeListener();
    void onDataChanging(const Eigen::MatrixXf &val);

private:
    myMatlabEngine *m_eng;
    MatIOArray mtVal;
    std::string mtScriptName;
};

