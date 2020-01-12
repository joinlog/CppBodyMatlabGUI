#ifndef __MATLAB_WRAPPER_HPP__
#define __MATLAB_WRAPPER_HPP__

//代码依赖：Matlab，Eigen，Boost 

#include <engine.h>
#include <string>
#include <iostream>
#include <Eigen/Eigen>
//#include <boost\algorithm\string.hpp>

inline std::string rndcolor(){
    std::string color = "[";
    color += std::to_string((rand() % 256) / 255.) + ",";
    color += std::to_string((rand() % 256) / 255.) + ",";
    color += std::to_string((rand() % 256) / 255.) + "]";
    return color;
}

class myMatArray
{
public:
    myMatArray() : _data(NULL){}
    myMatArray(size_t irows, size_t icols){
        resize(irows, icols);
    }
    myMatArray(const myMatArray &obj){
        if (obj._data){
            _data = mxCreateDoubleMatrix(obj.rows(), obj.cols(), mxREAL);
            memcpy(this->ptr(), obj.ptr(), sizeof(double)*rows()*cols());
        }
        else{
            _data = NULL;
        }
    }
    ~myMatArray(){ mxDestroyArray(_data); _data = NULL; }

    inline size_t rows() const { return _data ? mxGetM(_data) : 0; }
    inline size_t cols() const { return _data ? mxGetN(_data) : 0; }
    inline double* ptr() const { return _data ? mxGetPr(_data) : NULL; }

    bool resize(size_t irows, size_t icols){
        if (!_data){
            _data = mxCreateDoubleMatrix(irows, icols, mxREAL);
            return (_data != NULL);
        }
        if (rows() == irows && cols() == icols){
            return true;
        }
        mxDestroyArray(_data);
        _data = mxCreateDoubleMatrix(irows, icols, mxREAL);
        return (_data != NULL);
    }

    void get(Engine *ep, const char* var_name)
    {
        mxDestroyArray(_data); 
        _data = NULL;
        _data = engGetVariable(ep, var_name);
    }
    
    int put(Engine *ep, const char* var_name){
        return engPutVariable(ep, var_name, _data);
    }

    template<class EigenMat = Eigen::MatrixXf>
    void copy_from_eigen(const EigenMat &emat){
        if (emat.rows()*emat.cols() == 0){
            mxDestroyArray(_data); _data = NULL;
        }
        resize(emat.rows(), emat.cols());
        //std::cout << "myMatArray.this=" << this << ", private _date=" << _data << " emat.row=" << emat.rows() <<  ",emat.row=col" << emat.cols() << " mx.row=" <<rows() << ",mx.col=" << cols()<< std::endl;
        for (int c = 0; c < emat.cols(); c++){
            for (int r = 0; r < emat.rows(); r++){
                (*this)[r + c*(int)(emat.rows())] = emat(r, c);
            }
        }
    }

    template<class EigenMat = Eigen::MatrixXf>
    void copy_to_eigen(EigenMat &emat) {
        if (rows()*cols() == 0) {
            return;
        }
        emat.resize(rows(), cols());
        //std::cout << "myMatArray.this=" << this << ", private _date=" << _data << " emat.row=" << emat.rows() <<  ",emat.row=col" << emat.cols() << " mx.row=" <<rows() << ",mx.col=" << cols()<< std::endl;
        for (int c = 0; c < emat.cols(); c++) {
            for (int r = 0; r < emat.rows(); r++) {
                emat(r, c) = (*this)[r + c*(int)(emat.rows())];
            }
        }
    }

    inline double& operator[](int i){
        return ptr()[i];
    }

private:
    mxArray *_data;
};


class myMatlabEngine
{
private:
    myMatlabEngine(const myMatlabEngine &obj){}
public:
    myMatlabEngine(){
        _engine = engOpen(NULL);
        if (!_engine){
            std::cerr << "failed to open MATLAB engine!" << std::endl;
        }
        else{
            std::cout << "MATLAB has been started successfully!" << std::endl;
        }
    }
    ~myMatlabEngine(){
        // if you are testing algorithm, you are encouraged to keep the line below bing committed.
        //engClose(_engine); _engine = NULL;
    }

    // line_spec : "LineStyle" + "Marker" + "Color", e.g. "-or"
    // for line
    // "LineStyle" = {"none", "-", ":", "-."}
    // "LineWidth" = 0.5
    // "Color" = {[0 0.4470 0.7410] (default) | RGB triplet | {y,m,c,r,g,b,w,k} | 'none'}
    // for Marker
    // "Marker" = {"none", "o", "+", "*", ".", "x", "s", "d", "^", "v", ">", "<", 'p', 'h'}
    // "MarkerEdgeColor" = 'auto' (default) | 'none' | RGB triplet | {y,m,c,r,g,b,w,k}
    // "MarkerFaceColor" = 'auto' (default) | 'none' | RGB triplet | {y,m,c,r,g,b,w,k}
    // "MarkerSize" = 6
    template<class TMatX = Eigen::MatrixXf, class TMatY = Eigen::MatrixXf, class TMask = Eigen::MatrixXi>
    int plot(const TMatX &X, const TMatY &Y, const TMask &mask,
        std::string nm0  = "",
        std::string nm1  = "", std::string nm2  = "",
        std::string nm3  = "", std::string nm4  = "",
        std::string nm5  = "", std::string nm6  = "",
        std::string nm7  = "", std::string nm8  = "",
        std::string nm9  = "", std::string nm10 = "",
        std::string nm11 = "", std::string nm12 = "",
        std::string nm13 = "", std::string nm14 = ""
    ){
        myMatArray MX, MY, MS;

        MX.copy_from_eigen(X); MX.put(_engine, "MX");
        MY.copy_from_eigen(Y); MY.put(_engine, "MY");
        MS.copy_from_eigen(mask); MS.put(_engine, "MS");
        std::string plot_code = "MX(MS>0), MY(MS>0)";
        std::string code;

#define EVL_CODE(_ARG0,_ARG1) code = var_plot_code(nm##_ARG0, nm##_ARG1); if(code != ""){ plot_code += ", " + code;}
        code = var_plot_code(nm0, "");
        if (code != ""){
            plot_code += ", " + code;
            EVL_CODE(1, 2);EVL_CODE(3, 4);EVL_CODE(5, 6);EVL_CODE(7, 8);EVL_CODE(9, 10);EVL_CODE(11, 12);EVL_CODE(13, 14);
        }
        else{
            EVL_CODE(0, 1);EVL_CODE(2, 3);EVL_CODE(4, 5);EVL_CODE(6, 7);EVL_CODE(8, 9);EVL_CODE(10, 11);EVL_CODE(12, 13);
        }
#undef EVL_CODE
        plot_code = "plot(" + plot_code + ");";
        std::cout << plot_code << std::endl;
        exec(plot_code);
        return 0;
    }


    // line_spec : "LineStyle" + "Marker" + "Color", e.g. "-or"
    // for line
    // "LineStyle" = {"none", "-", ":", "-."}
    // "LineWidth" = 0.5
    // "Color" = {[0 0.4470 0.7410] (default) | RGB triplet | {y,m,c,r,g,b,w,k} | 'none'}
    // for Marker
    // "Marker" = {"none", "o", "+", "*", ".", "x", "s", "d", "^", "v", ">", "<", 'p', 'h'}
    // "MarkerEdgeColor" = 'auto' (default) | 'none' | RGB triplet | {y,m,c,r,g,b,w,k}
    // "MarkerFaceColor" = 'auto' (default) | 'none' | RGB triplet | {y,m,c,r,g,b,w,k}
    // "MarkerSize" = 6
    template<class TMatX = Eigen::MatrixXf, class TMatY = Eigen::MatrixXf>
    int plot(const TMatX &X, const TMatY &Y,
        std::string nm0  = "",
        std::string nm1  = "", std::string nm2  = "",
        std::string nm3  = "", std::string nm4  = "",
        std::string nm5  = "", std::string nm6  = "",
        std::string nm7  = "", std::string nm8  = "",
        std::string nm9  = "", std::string nm10 = "",
        std::string nm11 = "", std::string nm12 = "",
        std::string nm13 = "", std::string nm14 = ""
    ){
        myMatArray MX, MY;
        MX.copy_from_eigen(X); MX.put(_engine, "MX");
        MY.copy_from_eigen(Y); MY.put(_engine, "MY");
        std::string plot_code = "MX, MY";
        std::string code;
#define EVL_CODE(_ARG0,_ARG1) code = var_plot_code(nm##_ARG0, nm##_ARG1); if(code != ""){ plot_code += ", " + code;}
        code = var_plot_code(nm0, "");
        if (code != ""){
            plot_code += ", " + code;
            EVL_CODE(1, 2);EVL_CODE(3, 4);EVL_CODE(5, 6);EVL_CODE(7, 8);EVL_CODE(9, 10);EVL_CODE(11, 12);EVL_CODE(13, 14);
        }
        else{
            EVL_CODE(0, 1);EVL_CODE(2, 3);EVL_CODE(4, 5);EVL_CODE(6, 7);EVL_CODE(8, 9);EVL_CODE(10, 11);EVL_CODE(12, 13);
        }
#undef EVL_CODE
        plot_code = "plot(" + plot_code + ");";
        std::cout << plot_code << std::endl;
        exec(plot_code);
        return 0;
    }

#define TEMPLATE_PLOT(ARG3) \
    template<class TMatX = Eigen::MatrixXf, class TMatY = Eigen::MatrixXf> \
    int plot(const TMatX &X, const TMatY &Y, \
        ARG3 nm0 = "" , \
        std::string nm1  = "", std::string nm2  = "", \
        std::string nm3  = "", std::string nm4  = "", \
        std::string nm5  = "", std::string nm6  = "", \
        std::string nm7  = "", std::string nm8  = "",   \
        std::string nm9  = "", std::string nm10 = "",   \
        std::string nm11 = "", std::string nm12 = "",   \
        std::string nm13 = "", std::string nm14 = ""){  \
        return plot(X, Y, std::string(nm0), nm1, nm2, nm3, nm4, nm5, nm6, nm7, nm8, nm9, nm10, nm11, nm12, nm13, nm14); \
    }

    TEMPLATE_PLOT(char*);
    TEMPLATE_PLOT(const char*);
#undef TEMPLATE_PLOT

    int exec(std::string cmd){
        return engEvalString(_engine, cmd.c_str());
    }
    
    Engine *GetEngine()
    {
        return _engine;
    }
    
protected:
    std::string var_plot_code(std::string nm, std::string var){
        //boost::trim(nm); boost::trim(var);
        if (nm == ""){
            return "";
        }
        std::string code = "'" + nm + "'";

        if (var == ""){
            return (nm[0] < 'A' || nm[0] > 'Z') ? code : "";
        }
        if (nm == "LineStyle" || nm == "Marker"){ // string
            // 'LineStyle', '-'
            return code + ", '" + var + "'";
        }
        if (nm == "LineWidth" || nm == "MarkerSize"){ // positive number
            // 'LineWidth', 0.5
            return code + ",  " + var;
        }
        if (nm == "Color" || nm == "MarkerEdgeColor" || nm == "MarkerFaceColor"){
            if (var[0] == '['){
                return code + ",  " + var;
            }
            else{
                return code + ", '" + var + "'";
            }
        }
        return "";
    }

private:
    Engine *_engine;
};



class MatIOArray
{
public :
    MatIOArray():_engine(NULL){mMA = new myMatArray();}
    MatIOArray(Engine *_engine):_engine(_engine)
    {
        mMA = new myMatArray();
    }
    MatIOArray(Engine *_engine, const char *var_name):_engine(_engine),varName(var_name)
    {
        mMA = new myMatArray();
    }
    ~MatIOArray(){ delete mMA; mMA = NULL;}

    void SetEngine(Engine *_engine)
    {
        this->_engine = _engine;
    }
        
    void SetVarName(const char* var_name)
    {
        this->varName = var_name;
    }

    template<class EigenMat = Eigen::MatrixXf>
    void put(const EigenMat &emat)
    {
        if (_engine == NULL || varName.empty() || mMA == NULL)
        {
            std::cout << "set Engine & VarName first!" << std::endl;
        }
        mMA->copy_from_eigen(emat);
        mMA->put(_engine, varName.c_str());
    }

    template<class EigenMat = Eigen::MatrixXf>
    void get(EigenMat &emat) 
    {
        mMA->get(_engine, varName.c_str());
        mMA->copy_to_eigen(emat);
    }
    
private:
    Engine *_engine; 
    std::string varName;
    myMatArray *mMA;
};

#endif

