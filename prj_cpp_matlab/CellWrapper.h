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
#include "matlabWrapper.h"

class CellWrapper
{
public:
    CellWrapper();
    CellWrapper(int mi, int mj, int mradius, int mcellNum, int mminNodeNum, int mmaxNodeNum, RateStatus_t mminRate, RateStatus_t mmaxRate);
    ~CellWrapper();
    void InitCellWrapper(int mi, int mj, int mradius, int mcellNum, int mminNodeNum, int mmaxNodeNum, RateStatus_t mminRate, RateStatus_t mmaxRate, float mlambda,
    float mtau,
    float mmiu,
    float msigma,
    float mepsilon, float omega);
    void InitCells();
    void UpdateCells();
    
    void Cells2EgineMat(Eigen::MatrixXf &em);
    
private:
    void InitCellPos(std::vector<int> &a);
    void NewCells(std::vector<int> &a);
    void NewACell(int id, int i, int j);
    int MakeIdUsePos(int i, int j);
    void InitNeighborCells();
    void GetNeighborPos(int i, int j, int &mini, int &maxi, int &minj, int &maxj);
    void GetNeightborCells(int i, int j, std::vector<newCell *> &vcCells);
    
    void Cell2EgineMat(newCell &nc, Eigen::MatrixXf &em, int row);

private:
    int imax;
    int jmax;
    int radius;
    int cellNum; // 生成umpCells的个数
    int minNodeNum; //每个Cell中最小节点个数
    int maxNodeNum; //每个Cell中最大节点个数
    RateStatus_t minRate; // 各个状态占有最大比率,用于初始化cell
    RateStatus_t maxRate; // 各个状态占有最大比率,用于初始化cell
    std::unordered_map<int, newCell*> umpCells; // cell id 作为key
    
    float lambda; // λ
    float tau; // τ
    float miu; //μ
    float sigma; //σ,ς
    float epsilon; // ε
    float omega;   //例如ω= λ / 8
};

#endif /* CELLWRAPPER_H */

