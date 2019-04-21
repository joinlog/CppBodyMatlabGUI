/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newCell.cpp
 * Author: zy
 * 
 * Created on 2019年4月4日, 下午3:49
 */

#include <cmath>
#include <iostream>
#include "newCell.h"
#include "myBaseUtils.h"

newCell::newCell():id(0), ireal(0),jreal(0),nodeNum(0),lambda(0), tau(0), miu(0),sigma(0),epsilon(0),omega(0), fp(NULL)
{
    memset(rs, 0, sizeof(rs));
}

newCell::newCell(int mid, int mi, int mj, int mNodeNum,float mlambda,
    float mtau,
    float mmiu,
    float msigma,
    float mepsilon, float momega, FILE *mfp):id(mid), ireal(mi),jreal(mj),nodeNum(mNodeNum),
        lambda(mlambda), tau(mtau), miu(mmiu),sigma(msigma),epsilon(mepsilon),omega(momega), fp(mfp)
{
    memset(rs, 0, sizeof(rs));
}

newCell::newCell(const newCell& a)
{
    //memcpy(this, &a, sizeof(newCell));
    std::cout << "newCell(const newCell& a)" << std::endl;
}
newCell::newCell( newCell&& a)
{
    //memcpy(this, &a, sizeof(newCell));
    std::cout << "newCell( newCell&& a)" << std::endl;
}

newCell::~newCell()
{
}

newCell & newCell::operator =(const newCell& a)
{
    //memcpy(this, &a, sizeof(newCell));
    std::cout << "operator =(const newCell& a)" << std::endl;
    return *this;
}

void newCell::SetCurrentRateStatusS(float val)
{
    if (!std::isfinite(val))
    {
        std::cout<<"Set S Nan"<<std::flush<<std::endl;
        DumpStr();
        DumpNeighborRS();
        exit(1);
    }
    SetRateStatus(val, sfS, tcCur);
}


void newCell::SetCurrentRateStatusE(float val)
{
    if (!std::isfinite(val))
    {
        std::cout<<"Set E Nan"<<std::flush<<std::endl;
        DumpStr();
        DumpNeighborRS();
        exit(1);
    }
    SetRateStatus(val, sfE, tcCur);
}


void newCell::SetCurrentRateStatusI(float val)
{
    if (!std::isfinite(val))
    {
        std::cout<<"Set I Nan"<<std::flush<<std::endl;
        DumpStr();
        DumpNeighborRS();
        exit(1);
    }
    SetRateStatus(val, sfI, tcCur);
}


void newCell::SetCurrentRateStatusR(float val)
{
    if (!std::isfinite(val))
    {
        std::cout<<"Set R Nan"<<std::flush<<std::endl;
        DumpStr();
        DumpNeighborRS();
        exit(1);
    }
    SetRateStatus(val, sfR, tcCur);
}

void newCell::SetRateStatus(float val, StatusFlag_e st, TimeCount_e tc)
{
    SetRateStatusRes(val, st, rs[tc]);
}

void newCell::SetRateStatusRes(float val, StatusFlag_e st, RateStatus_t &mRs)
{
    switch (st)
    {
    case sfS:
        mRs.s = val;
        break;
    case sfE:
        mRs.e = val;
        break;
    case sfI:
        mRs.i = val;
        break;
    case sfR:
        mRs.r = val;
        break;
    default:
        std::cout<<"can not be here!"<<std::endl;
        break;
    }
}

float newCell::GetPreRateStatusS()
{
    return GetRateStatus(sfS, tcPre);
}

float newCell::GetPreRateStatusE()
{
    return GetRateStatus(sfE, tcPre);
}

float newCell::GetPreRateStatusI()
{
    return GetRateStatus(sfI, tcPre);
}

float newCell::GetPreRateStatusR()
{
    return GetRateStatus(sfR, tcPre);
}

float newCell::GetRateStatus(StatusFlag_e st, TimeCount_e tc)
{
    return GetRateStatusRes( st, rs[tc]);
}

float newCell::GetRateStatusRes(StatusFlag_e st, RateStatus_t &mRs)
{
    float val = -1.0;
    switch (st)
    {
    case sfS:
        val = mRs.s;
        break;
    case sfE:
        val = mRs.e;
        break;
    case sfI:
        val = mRs.i;
        break;
    case sfR:
        val = mRs.r;
        break;
    default:
        std::cout<<"can not be here!"<<std::endl;
        break;
    }
    return val;
}

void newCell::SetRateStatusAll(RateStatus_t rsVal, TimeCount_e tc)
{
    memcpy(rs + tc, &rsVal, sizeof(RateStatus_t));
}

int newCell::GetNodeNum()
{
    return nodeNum;
}

void newCell::SetCellsId(std::vector<newCell *> vcCellsId)
{
    //cellsId.clear();
    cellsId.assign(vcCellsId.begin(), vcCellsId.end());
}

std::vector<newCell *> &newCell::GetCellsId()
{
    return cellsId;
}

void newCell::InitRateStatus(RateStatus_t& maxRs, RateStatus_t& minRs)
{
    RateStatus_t rs;
    CalcRateStatus(maxRs, minRs, rs);
    rs.tm = 0;
    SetRateStatusAll(rs, tcPre);
    rs.tm = 1;
    SetRateStatusAll(rs, tcCur);
}

void newCell::CalcRateStatus(RateStatus_t &maxRs, RateStatus_t &minRs, RateStatus_t& rs)
{
    rs.s = myBaseUtils::myRand(minRs.s, maxRs.s);
    rs.e = myBaseUtils::myRand(minRs.e, maxRs.e);
    rs.i = myBaseUtils::myRand(minRs.i, maxRs.i);
    rs.r = 1 - rs.s - rs.e - rs.i;
    
}

void newCell::CopyCurrent2PreviousRateStatus()
{
    rs[tcPre] = rs[tcCur];
}

void newCell::CalcCurrentRateStatus()
{
    SetCurrentRateStatusS(CalcCurS());
    SetCurrentRateStatusE(CalcCurE());
    SetCurrentRateStatusI(CalcCurI());
    SetCurrentRateStatusR(CalcCurR());
}

float newCell::CalcCurS()
{
    float preS = GetPreRateStatusS();
    float preI = GetPreRateStatusI();
    float numRate = SigmaSumNumRateI();
    return (preS - (lambda + tau) * preS *(preI + numRate) + miu *(1 - preS) );
}

float newCell::CalcCurE()
{
    float preS = GetPreRateStatusS();
    float preI = GetPreRateStatusI();
    float preE = GetPreRateStatusE();
    float numRate = SigmaSumNumRateI();
    return (1 - sigma - miu) * preE + lambda * preS * ( preI + numRate);
}

float newCell::CalcCurI()
{
    float preS = GetPreRateStatusS();
    float preI = GetPreRateStatusI();
    float preE = GetPreRateStatusE();
    float numRate = SigmaSumNumRateI();
    return (1 - epsilon - miu) * preI + sigma * preE + tau * preS * ( preI + numRate);
}

float newCell::CalcCurR()
{
    float preR = GetPreRateStatusR();
    float preI = GetPreRateStatusI();
    return (1 - miu) * preR + epsilon * preI;
}

float newCell::SigmaSumNumRateI()
{
    float sumNodeNum = 0;
    unsigned int n = cellsId.size();
    for (unsigned int i = 0; i < n; ++i)
    {
        sumNodeNum += ((float)cellsId[i]->GetNodeNum()) * cellsId[i]->GetPreRateStatusI();
    }
    float sumSigma = sumNodeNum / ((float)GetNodeNum());
    return sumSigma * omega; // 相当于 ωαβ
}

void newCell::DumpStr()
{
    printf("\nid, i, j, nodeNum, neighbor num\n %d, %d, %d, %d, %d\n", id, ireal, jreal, nodeNum, cellsId.size());
    DumpRateStatus(rs[tcPre]);
    DumpRateStatus(rs[tcCur]);
}

void newCell::DumpNeighborRS()
{
    for (auto elem : cellsId)
    {
        elem->DumpStr();
    }

}
void newCell::DumpRateStatus(RateStatus_t& rs)
{
    printf("S, E, I, R\n %.2f, %.2f, %.2f, %.2f\n", rs.s, rs.e, rs.i, rs.r);
    
    fprintf(fp, "%d, %.2f, %.2f, %.2f, %.2f\n", id, rs.s, rs.e, rs.i, rs.r);
} 
