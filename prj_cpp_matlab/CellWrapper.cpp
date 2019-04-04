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

CellWrapper::CellWrapper():i(0),j(0),cellNum(0),minNodeNum(0),maxNodeNum(0),minRate(0),maxRate(0)
{
}

CellWrapper::CellWrapper(int mi, int mj, int mcellNum, int mminNodeNum, int mmaxNodeNum, RateStatus_t mminRate, RateStatus_t mmaxRate):
i(mi),j(mj),cellNum(mcellNum), minNodeNum(mminNodeNum),maxNodeNum(mmaxNodeNum),minRate(mminRate),maxRate(mmaxRate)
{
    
}

CellWrapper::~CellWrapper()
{
}

void CellWrapper::InitCells()
{
    // 根据最大最小值初始化所有的cell
}
