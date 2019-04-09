% global h_start;
% global h_end;
% 
% global h_text_start;
% global h_text_end;
% 
% global h_rts;
% global h_text_rts;
% 
% global h_select_object;
% global h_agv_boxes;
% global h_text_agv_id;

global CellsParam;
global FuncParam;
global RateRange;
global mStatistic;

% global mRts;
% global mBoxes;
% 
% global g_agv_code;
% global g_try_code;
% global g_clm_code;

axis equal;
% PlotMap('..\..\data\');



% // 从matlab脚本读入数据初始化CellWrapper
% //    int imax;
% //    int jmax;
% //    int radius;
% //    int cellNum; // 生成umpCells的个数
% //    int minNodeNum; //每个Cell中最小节点个数
% //    int maxNodeNum; //每个Cell中最大节点个数

CellsParam = [100, 100, 20, 3000, 6, 10];
% //    float lambda; // λ
% //    float tau; // τ
% //    float miu; //μ
% //    float sigma; //σ,?
% //    float epsilon; // ε
FuncParam = [0.064, 0.2572, 0.053, 0.3028, 0.3298];
% //    RateStatus_t minRate; // 各个状态占有最大比率,用于初始化cell
% //    RateStatus_t maxRate; // 各个状态占有最大比率,用于初始化cell
RateRange = [0.8 0 0.2 0
    0.8 0 0.2 0
        ];
    
mStatistic = [];
    
% h_start = []; % 1行n列,访问格式h_start(i)
% h_end = []; % 1行n列
% h_text_start = []; % 1行n列
% h_text_end = []; % 1行n列
% 
% h_rts = []; % 1行n列
% h_text_rts = []; % 1行n列
% 
% 
% h_select_object=[];
% 
% g_agv_code = 7103118;%agv='a''g''v'=97,103,118,860=97103118
% g_try_code = 6114121;%try=116114121 
% g_clm_code = 9108109;% clm=99108109
% h_agv_boxes = []; %1行n列，用g_agv_code，g_try_code，g_clm_code间隔开要画的boxes的句柄
% %格式：g_agv_code|860|g_clm_code|句柄|g_try_code|句柄|g_agv_code。。。。。。
% %实例 97103118 860 99108109 . . . . . . g_try_code . . . 97103118 861 ......
% h_text_agv_id = [];

set(gcf,'WindowButtonDownFcn',@ButttonDownFcn2);
set(gcf,'WindowKeyPressFcn',{@keypressCallback2});