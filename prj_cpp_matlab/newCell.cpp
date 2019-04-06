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

#include "newCell.h"
#include "myBaseUtils.h"

newCell::newCell():id(0), ireal(0),jreal(0),nodeNum(0)
{
    memset(rs, 0, sizeof(rs));
}

newCell::newCell(int mid, int mi, int mj, int mNodeNum):id(mid), ireal(mi),jreal(mj),nodeNum(mNodeNum)
{
    memset(rs, 0, sizeof(rs));
}

newCell::~newCell()
{
}

void newCell::SetCurrentRateStatusS(float val)
{
    SetRateStatus(val, sfS, tcCur);
}


void newCell::SetCurrentRateStatusE(float val)
{
    SetRateStatus(val, sfE, tcCur);
}


void newCell::SetCurrentRateStatusI(float val)
{
    SetRateStatus(val, sfI, tcCur);
}


void newCell::SetCurrentRateStatusR(float val)
{
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
    return GetRateStatus(sfS, tcPre);
}

float newCell::GetPreRateStatusI()
{
    return GetRateStatus(sfS, tcPre);
}

float newCell::GetPreRateStatusR()
{
    return GetRateStatus(sfS, tcPre);
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
    cellsId.clear();
    cellsId.assign(cellsId.begin(), vcCellsId.begin(), vcCellsId.end());
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
    rs.s = myBaseUtils::rand(minRs.s, maxRs.s);
    rs.e = myBaseUtils::rand(minRs.e, maxRs.e);
    rs.i = myBaseUtils::rand(minRs.i, maxRs.i);
    rs.r = 1 - rs.s - rs.e - rs.i;
    
}
