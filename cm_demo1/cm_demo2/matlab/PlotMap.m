function  PlotMap( map_fold )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
% ������ͼ
global nodes;
nodes = xlsread([map_fold(1:end),'t_vertex.csv']);


hold on;
plot(nodes(:,2), nodes(:,3), 'c.');
% ����
% for i = 1:size(nodes,1);
%     if nodes(i, 2) == 1
%         if nodes(i, 19) ~= 0
%             line([nodes(i,6) nodes(i,11)], [nodes(i,7) nodes(i,12)]);
%         end
%     else
%         plot(nodes(i,6), nodes(i, 7), 'o');
%     end
% end
% ����
% for i = 1:size(nodes,1);
%     if nodes(i, 19) == 0
%         if nodes(i,11) - nodes(i, 6) + nodes(i,12) - nodes(i, 7) > 0
%             line([nodes(i,6) nodes(i,11)], [nodes(i,7) nodes(i,12)], 'color', 'r');
%         else
%             line([nodes(i,6) nodes(i,11)], [nodes(i,7) nodes(i,12)], 'color', 'g');
%         end
%     end
% end

%axis equal;
hold on;

%set(gcf,'Position',[134 300 560 420]); %���ñ����ߴ�

%set(gcf,'WindowButtonDownFcn',@ButtonDownFcnShowEdge);
end



