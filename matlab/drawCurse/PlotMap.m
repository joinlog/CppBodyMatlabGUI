map_fold='';

global nodes;
nodes = xlsread([map_fold(1:end),'result.csv']);


%% Post processing for unimportable data.
% No unimportable data rules were applied during the import, so no post
% processing code is included. To generate code which works for
% unimportable data, select unimportable cells in a file and regenerate the
% script.

%% Allocate imported array to column variable names
S=nodes(:,2);
E=nodes(:,3);
I=nodes(:,4);
R=nodes(:,5);

%% '-s'  表示方格; '-p' 表示五角星;'-d' 表示菱形 '-h' 表示六角形  '-+' 表示用加号 '-o'  表示用圈 '-*'  表示星号
%% -     solid; :     dotted; --    dashed   ; -.    dashdot 
%%
[m,n]=size(nodes);
t=1:m;
%plot(t,VarName1,'+b',t,VarName2,'*g',t,VarName3,'or');
%plot(t,VarName1,'-sb',t,VarName2,'-og',t,VarName3,'-*r');
plot(t,S,'-s',t,E,'-o',t,I,'-*r',t,R,'-d');
legend('S','E','I','R');
%title('Title','FontName','Times New Roman','FontWeight','Bold','FontSize',16)
xlabel('Time','FontName','Times New Roman','FontSize',14)
ylabel('Cell Status Percentage','FontName','Times New Roman','FontSize',14,'Rotation',90)


hold on;
