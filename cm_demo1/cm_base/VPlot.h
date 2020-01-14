#pragma once
#include "IDataChangeNotifier.h"

//此DLL中的所有文件都是在定义-DVPlot_API_EXPORTS符号编译的；
//使用此DLL的任何其他项目上不应定义此符号。
//这样，源文件中包含此文件的任何其他项目都会将VPlot_API定义的函数视为从DLL导入的，
//而DLL内部的文件则将VPlot_API定义的函数视为从DLL导出的。
#ifdef VPlot_API_EXPORTS
#define VPlot_API __declspec(dllexport)
#else
#define VPlot_API __declspec(dllimport)
#endif // Algo_API_EXPORTS


class VPlot_API VPlot :
    public IDataChangeNotifier
{
public:
    VPlot(std::string matScriptName, std::string matVarName);
    ~VPlot();

    const Eigen::MatrixXf &GetVal();
    void SetVal(Eigen::MatrixXf &val);

private:
    void registerListenner(IDataChangeListener *l);
    void removeListenner(IDataChangeListener *l);
    void notify();
    void request();

private:
    IDataChangeListener *ml;
    Eigen::MatrixXf mVal;
};

