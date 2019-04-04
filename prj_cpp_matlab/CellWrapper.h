/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CellWrapper.h
 * Author: zy
 *
 * Created on 2019年4月4日, 下午4:33
 */

#ifndef CELLWRAPPER_H
#define CELLWRAPPER_H

#include <unordered_map>
#include "newCell.h"

class CellWrapper
{
public:
    CellWrapper();
    CellWrapper(int mi, int mj, int mcellNum, int mminNodeNum, int mmaxNodeNum, RateStatus_t mminRate, RateStatus_t mmaxRate);
    ~CellWrapper();
    void InitCells();
private:
    int i;
    int j;
    int cellNum; // 生成umpCells的个数
    int minNodeNum; //每个Cell中最小节点个数
    int maxNodeNum; //每个Cell中最大节点个数
    RateStatus_t minRate; // 各个状态占有最大比率,用于初始化cell
    RateStatus_t maxRate; // 各个状态占有最大比率,用于初始化cell
    std::unordered_map<int, newCell> umpCells; // cell id 作为key
};

#endif /* CELLWRAPPER_H */
