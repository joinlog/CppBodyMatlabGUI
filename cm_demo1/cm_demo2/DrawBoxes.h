#pragma once
#include "IDataChangeNotifier.h"
class DrawBoxes :
    public IDataChangeNotifier
{
public:
    DrawBoxes();
    ~DrawBoxes();

    void registerListenner(IDataChangeListener *l);
    void removeListenner(IDataChangeListener *l);
    void notify();

    const Eigen::MatrixXf &GetBoxes() { return mBoxes; }
    void SetBoxes(std::vector<float> &boxParam);
private:
    IDataChangeListener *ml;
    Eigen::MatrixXf mBoxes;
};

