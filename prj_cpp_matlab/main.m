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



% // ��matlab�ű��������ݳ�ʼ��CellWrapper
% //    int imax;
% //    int jmax;
% //    int radius;
% //    int cellNum; // ����umpCells�ĸ���
% //    int minNodeNum; //ÿ��Cell����С�ڵ����
% //    int maxNodeNum; //ÿ��Cell�����ڵ����

CellsParam = [100, 100, 20, 3000, 6, 10];
% //    float lambda; // ��
% //    float tau; // ��
% //    float miu; //��
% //    float sigma; //��,?
% //    float epsilon; // ��
FuncParam = [0.064, 0.2572, 0.053, 0.3028, 0.3298];
% //    RateStatus_t minRate; // ����״̬ռ��������,���ڳ�ʼ��cell
% //    RateStatus_t maxRate; // ����״̬ռ��������,���ڳ�ʼ��cell
RateRange = [0.8 0 0.2 0
    0.8 0 0.2 0
        ];
    
mStatistic = [];
    
% h_start = []; % 1��n��,���ʸ�ʽh_start(i)
% h_end = []; % 1��n��
% h_text_start = []; % 1��n��
% h_text_end = []; % 1��n��
% 
% h_rts = []; % 1��n��
% h_text_rts = []; % 1��n��
% 
% 
% h_select_object=[];
% 
% g_agv_code = 7103118;%agv='a''g''v'=97,103,118,860=97103118
% g_try_code = 6114121;%try=116114121 
% g_clm_code = 9108109;% clm=99108109
% h_agv_boxes = []; %1��n�У���g_agv_code��g_try_code��g_clm_code�����Ҫ����boxes�ľ��
% %��ʽ��g_agv_code|860|g_clm_code|���|g_try_code|���|g_agv_code������������
% %ʵ�� 97103118 860 99108109 . . . . . . g_try_code . . . 97103118 861 ......
% h_text_agv_id = [];

set(gcf,'WindowButtonDownFcn',@ButttonDownFcn2);
set(gcf,'WindowKeyPressFcn',{@keypressCallback2});