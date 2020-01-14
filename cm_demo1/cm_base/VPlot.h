#pragma once
#include "IDataChangeNotifier.h"

//��DLL�е������ļ������ڶ���-DVPlot_API_EXPORTS���ű���ģ�
//ʹ�ô�DLL���κ�������Ŀ�ϲ�Ӧ����˷��š�
//������Դ�ļ��а������ļ����κ�������Ŀ���ὫVPlot_API����ĺ�����Ϊ��DLL����ģ�
//��DLL�ڲ����ļ���VPlot_API����ĺ�����Ϊ��DLL�����ġ�
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

