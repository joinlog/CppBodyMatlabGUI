/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newCell.h
 * Author: zy
 *
 * Created on 2019年4月4日, 下午3:49
 */

#ifndef NEWCELL_H
#define NEWCELL_H
#include <iostream>
#include <vector>
#include <stdio.h>
#include <memory.h>
enum TimeCount_e
{
    tcPre,
    tcCur
};

enum StatusFlag_e
{
    sfS,
    sfE,
    sfI,
    sfR
};

typedef struct _rateStatus_t
{
    int tm;
    float s;
    float e;
    float i;
    float r;
}RateStatus_t;

class newCell
{
public:
    newCell();
    newCell(int mid, int mi, int mj, int mNodeNum, float mlambda,
    float mtau,
    float mmiu,
    float msigma,
    float mepsilon);
    newCell(const newCell & a);
    newCell(newCell && a);
    ~newCell();
    newCell & operator=( const newCell &a);
    int GetCellI() { return ireal; }
    int GetCellJ() { return jreal; }
    void SetCurrentRateStatusS(float val);
    void SetCurrentRateStatusE(float val);
    void SetCurrentRateStatusI(float val);
    void SetCurrentRateStatusR(float val);
    float GetPreRateStatusS();
    float GetPreRateStatusE();
    float GetPreRateStatusI();
    float GetPreRateStatusR();
    int GetNodeNum();
    void SetCellsId(std::vector<newCell *> vcCellsId);
    std::vector<newCell *> &GetCellsId();
    void InitRateStatus(RateStatus_t &maxRs, RateStatus_t &minRs);
    void CopyCurrent2PreviousRateStatus();
    void CalcCurrentRateStatus();
    
    void DumpStr();
private:
    void SetRateStatus(float val, StatusFlag_e st, TimeCount_e tc);
    void SetRateStatusRes(float val, StatusFlag_e st, RateStatus_t &mRs);
    float GetRateStatus(StatusFlag_e st, TimeCount_e tc);
    float GetRateStatusRes(StatusFlag_e st, RateStatus_t &mRs);
    
    void SetRateStatusAll(RateStatus_t rsVal, TimeCount_e tc);
    void CalcRateStatus(RateStatus_t &maxRs, RateStatus_t &minRs, RateStatus_t &rs);
    
        
    float CalcCurS();
    float CalcCurE();
    float CalcCurI();
    float CalcCurR();
    float SigmaSumNumRate();
    
    void DumpRateStatus(RateStatus_t &rs);
private:
    int id;
    int ireal;
    int jreal;
    int nodeNum; // 节点个数
    RateStatus_t rs[2];  // 存放t-1和t的状态比率
    std::vector<newCell *> cellsId; // 邻居范围内的cellid

    float lambda; // λ
    float tau; // τ
    float miu; //μ
    float sigma; //σ,ς
    float epsilon; // ε
};

#endif /* NEWCELL_H */

