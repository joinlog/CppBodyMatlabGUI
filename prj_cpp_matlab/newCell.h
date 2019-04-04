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
#include <vector>
enum _timeCount_e
{
    tcPre,
    tcCur
}TimeCount_e;

enum _statusFlag_e
{
    sfS,
    sfE,
    sfI,
    sfR
}StatusFlag_e;

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
    ~newCell();
    void SetCurrentRateStatusS(float val);
    void SetCurrentRateStatusE(float val);
    void SetCurrentRateStatusI(float val);
    void SetCurrentRateStatusR(float val);
    float GetPreRateStatusS();
    float GetPreRateStatusE();
    float GetPreRateStatusI();
    float GetPreRateStatusR();
    int GetNodeNum();
    void SetCellsId(std::vector<int> vcCellsId);
    std::vector<int> &GetCellsId();
private:
    void SetRateStatus(float val, StatusFlag_e st, TimeCount_e tc);
    void SetRateStatusRes(float val, StatusFlag_e st, RateStatus_t &mRs);
    float GetRateStatus(StatusFlag_e st, TimeCount_e tc);
    float GetRateStatusRes(StatusFlag_e st, RateStatus_t &mRs);
private:
    int id;
    int i;
    int j;
    int nodeNum; // 节点个数
    RateStatus_t rs[2];  // 存放t-1和t的状态比率
    std::vector<int> cellsId; // 邻居范围内的cellid
};

#endif /* NEWCELL_H */

