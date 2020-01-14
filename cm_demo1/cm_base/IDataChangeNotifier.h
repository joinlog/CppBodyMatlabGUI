#pragma once
#include <engine.h>
#include <string>
#include <iostream>
#include <Eigen/Eigen>
#include "IDataChangeListener.h"

class IDataChangeNotifier
{
public:
    virtual void registerListenner(IDataChangeListener *l) = 0;
    virtual void removeListenner(IDataChangeListener *l) = 0;
    virtual void notify() = 0;
};

