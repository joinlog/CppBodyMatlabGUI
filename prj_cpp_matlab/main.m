global h_start;
global h_end;

global h_text_start;
global h_text_end;

global h_rts;
global h_text_rts;

global h_select_object;
global h_agv_boxes;
global h_text_agv_id;

global mStart;
global mEnd;

global mRts;
global mBoxes;

global g_agv_code;
global g_try_code;
global g_clm_code;

axis equal;
PlotMap('..\..\data\');

h_start = []; % 1行n列,访问格式h_start(i)
h_end = []; % 1行n列
h_text_start = []; % 1行n列
h_text_end = []; % 1行n列

h_rts = []; % 1行n列
h_text_rts = []; % 1行n列


h_select_object=[];

g_agv_code = 7103118;%agv='a''g''v'=97,103,118,860=97103118
g_try_code = 6114121;%try=116114121 
g_clm_code = 9108109;% clm=99108109
h_agv_boxes = []; %1行n列，用g_agv_code，g_try_code，g_clm_code间隔开要画的boxes的句柄
%格式：g_agv_code|860|g_clm_code|句柄|g_try_code|句柄|g_agv_code。。。。。。
%实例 97103118 860 99108109 . . . . . . g_try_code . . . 97103118 861 ......
h_text_agv_id = [];

set(gcf,'WindowButtonDownFcn',@ButttonDownFcn2);
set(gcf,'WindowKeyPressFcn',{@keypressCallback2});