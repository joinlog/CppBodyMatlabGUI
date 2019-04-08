/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CellWrapper.cpp
 * Author: zy
 * 
 * Created on 2019年4月4日, 下午4:33
 */

#include "CellWrapper.h"
#include "myBaseUtils.h"

#include <cstdlib>
#include <cassert>

CellWrapper::CellWrapper():imax(0),jmax(0),radius(0),cellNum(0),minNodeNum(0),maxNodeNum(0)
{
    memset(&minRate, 0, sizeof(minRate));
    memset(&maxRate, 0, sizeof(maxRate));
}

CellWrapper::CellWrapper(int mi, int mj, int mradius, int mcellNum, int mminNodeNum, int mmaxNodeNum, RateStatus_t mminRate, RateStatus_t mmaxRate):
imax(mi),jmax(mj),radius(mradius), cellNum(mcellNum), minNodeNum(mminNodeNum),maxNodeNum(mmaxNodeNum),minRate(mminRate),maxRate(mmaxRate)
{
    
}

CellWrapper::~CellWrapper()
{
}

void CellWrapper::InitCellWrapper(int mi, int mj, int mradius, int mcellNum, int mminNodeNum, int mmaxNodeNum, RateStatus_t mminRate, RateStatus_t mmaxRate, float mlambda,
    float mtau,
    float mmiu,
    float msigma,
    float mepsilon)
{
    imax = mi;
    jmax = mj;
    radius = mradius;
    cellNum = mcellNum;
    minNodeNum = mminNodeNum;
    maxNodeNum = mmaxNodeNum;
    minRate = mminRate;
    maxRate = mmaxRate;
    lambda = mlambda;
    tau = mtau;
    miu = mmiu;
    sigma = msigma;
    epsilon = mepsilon;
}

void CellWrapper::InitCells()
{
    // 根据最大最小值初始化所有的cell
    std::vector<int> a;
    InitCellPos(a);
    
    NewCells(a);
    
    // 初始化cellsId
    InitNeighborCells();
    
}

void CellWrapper::UpdateCells()
{
    // 主要的逻辑程序，实现公式6
    std::unordered_map<int, newCell>::iterator umpit = umpCells.begin();
    for (; umpit != umpCells.end(); ++umpit)
    {
        umpit->second.CopyCurrent2PreviousRateStatus();
    }
    for (umpit = umpCells.begin(); umpit != umpCells.end(); ++umpit)
    {
        umpit->second.CalcCurrentRateStatus();
        umpit->second.DumpStr();
    }
}

void CellWrapper::Cells2EgineMat(Eigen::MatrixXf& em)
{
    // i,j,s,e,i,r  n*6 n行6列 即
    em.resize(umpCells.size(), 6);
    std::unordered_map<int, newCell>::iterator umpit = umpCells.begin();
    int row = 0;
    for (; umpit != umpCells.end(); ++umpit)
    {
        Cell2EgineMat(umpit->second, em, row);
        ++row;
    }
}

void CellWrapper::InitCellPos(std::vector<int> &a)
{
    srand(time(NULL));
    // i, j, cellNum
    a.resize(imax*jmax, 0); // 扩展空间i*j，默认值为0
    int k = 0;
    while(k < cellNum)
    {
        int mi = rand() % imax;
        int mj = rand() % jmax;
        if (a[mi *jmax + mj] == 0)
        {
            a[mi *jmax + mj] = 1;
            ++k;
        }
    }
    
    
}
// 根据a中的位置初始化cells
void CellWrapper::NewCells(std::vector<int> &a)
{
    for (int i = 0; i < imax; ++i)
    {
        for (int j = 0; j < jmax; ++j)
        {
            int id = MakeIdUsePos(i, j);
            if (a[id] != 0)
            {
                NewACell(id, i, j);
            }
        }
    }
    
}

void CellWrapper::NewACell(int id, int i, int j)
{
    int mNodeNum = myBaseUtils::myRand(minNodeNum, maxNodeNum);
    newCell nc(id, i, j, mNodeNum, lambda, tau, miu, sigma, epsilon);
    umpCells.insert(std::pair<int, newCell>(id, nc));
    // 初始化RateStatus_t
    std::unordered_map<int, newCell>::iterator umpit = umpCells.find(id);
    if (umpit ==  umpCells.end())
    {
        return ;
    }

    umpit->second.InitRateStatus(maxRate, minRate);
}

int CellWrapper::MakeIdUsePos(int i, int j)
{
    return i * jmax + j;
}

void CellWrapper::InitNeighborCells()
{
    for (int i = 0; i < imax; ++i)
    {
        for (int j = 0; j < jmax; ++j)
        {
            int id = MakeIdUsePos(i, j);
            std::unordered_map<int, newCell>::iterator umpit = umpCells.find(id);
            if (umpit == umpCells.end())
            {
                continue;
            }
            std::vector<newCell *> mCells;
            GetNeightborCells(mCells);
            umpit->second.SetCellsId(mCells);
        }
    }
    
}


void CellWrapper::GetNeighborPos(int i, int j, int& mini, int& maxi, int& minj, int& maxj)
{
    mini = myBaseUtils::cutValue(i - radius, 0, imax - 1);
    maxi = myBaseUtils::cutValue(i + radius, 0, imax - 1);
    minj = myBaseUtils::cutValue(j - radius, 0, jmax - 1);
    maxj = myBaseUtils::cutValue(j + radius, 0, jmax - 1);
}

void CellWrapper::GetNeightborCells(std::vector<newCell*> vcCells)
{
    int mini;
    int maxi;
    int minj;
    int maxj;
    
    for (int i = mini; i <= maxi; ++i)
    {
        for (int j = minj; j <= maxj; ++j)
        {
            GetNeighborPos(i, j, mini, maxi, minj, maxj);
            int id = MakeIdUsePos(i, j);
            std::unordered_map<int, newCell>::iterator umpit = umpCells.find(id);
            if (umpit == umpCells.end())
            {
                continue;
            }
            vcCells.push_back(&(umpit->second));
        }
    }
}

void CellWrapper::Cell2EgineMat(newCell& nc, Eigen::MatrixXf & em, int row)
{
    em(row, 0) = nc.GetCellI();
    em(row, 1) = nc.GetCellJ();
    
    em(row, 2) = nc.GetPreRateStatusS();
    em(row, 3) = nc.GetPreRateStatusE();
    em(row, 4) = nc.GetPreRateStatusI();
    em(row, 5) = nc.GetPreRateStatusR();
}
