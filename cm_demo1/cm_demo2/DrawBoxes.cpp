
#include "DrawBoxes.h"


DrawBoxes::DrawBoxes() : ml(nullptr)
{
}


DrawBoxes::~DrawBoxes()
{
}

void DrawBoxes::registerListenner(IDataChangeListener *l)
{
    ml = l;
}

void DrawBoxes::removeListenner(IDataChangeListener *l)
{
    ml = nullptr;
}

void DrawBoxes::notify()
{
    if (ml != nullptr)
    {
        ml->onDataChanging(GetBoxes());
    }
    
}

void DrawBoxes::SetBoxes(std::vector<float> &boxParam)
{
    int mCols = 5;
    mBoxes.resize(boxParam.size() / mCols, mCols);
    for (int c = 0; c < mBoxes.cols(); c++)
    {
        for (int r = 0; r < mBoxes.rows(); r++) 
        {
            mBoxes(r, c) = boxParam[c + r * mBoxes.cols()];
        }
    }
    //std::cout << mBoxes << std::endl;
}
