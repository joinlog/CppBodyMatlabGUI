function ButttonDownFcn2(src,event)
global h_start;
global h_end;
global h_text_start;
global h_text_end;

global h_qc;
global h_text_qc;

global h_select_object;
global h_text_select_object;


pt = get(gca,'CurrentPoint');
disp([num2str(pt(1,1)), ',', num2str(pt(1,2)) ]);
if h_text_select_object ~= 0
    delete(h_text_select_object);
    h_text_select_object = 0;
end
disp('gco');
%gco
if abs(gco - h_start) <= 1
    disp('select start');
    h_select_object = h_start;
    h_text_select_object = text(pt(1,1),pt(1,2),'select start');
elseif abs(gco - h_end) <= 1
    disp('select end');
    h_select_object = h_end;
    h_text_select_object = text(pt(1,1),pt(1,2),'select end');
    
else
    
    [m,n] = size(h_qc);
    for i = 1 : n
        h_qc(i)
        if abs(gco - h_qc(i)) <= 1
            disp('select qc');
            h_select_object = h_qc(i);
            h_text_select_object = text(pt(1,1),pt(1,2),['select qc ',num2str(i)]);
            break;
        end
    end
end


% pt = get(gca,'CurrentPoint');
% x = pt(1,1);
% y = pt(1,2);
% idx = point2idx(data,pt);
% if  idx ~= 0
%     id = data(idx, 1);
%     lx = data(idx, 2);
%     ly = data(idx, 3);
%     x = data(idx,4);
%     y = data(idx,5);
% else
%     id = 0;
%     lx = 0;
%     ly = 0;
% end
% 
% 
% 
% 
% if h ~= 0
%     delete(h);
%     h = 0;
% end
% lane_id = 0;
% if ly ~= 0
%     lane_idx = find(lanes(:,2) == ly);
%     for i = 1:length(lane_idx)
%         start_y = lanes(lane_idx(i),4) / 100;
%         end_y = lanes(lane_idx(i), 6) / 100;
%         if (y - start_y) * (end_y - y) >= 0
%             lane_id = lanes(lane_idx(i), 1);
%             break;
%         end
%     end
% end
% s = ['x =',num2str(x),', y=',num2str(y),', Nid=',num2str(id),', Lx=',num2str(lx),', Ly=',num2str(ly),', lane=', num2str(lane_id)];
% 
% 
% h = text(x,y - 20,s);
% %plot(x,y,'ro','markersize',3);
% fprintf('x=%f,y=%f,id=%d,lx=%d,ly=%d\n',x,y,id,lx,ly);
% 
% global h_cal;
% 
% if h_cal ~= 0
%     delete(h_cal);
%     h_cal = text(wpts(1, 1) + 50,280,'参数变化，请重新计算','color','r');
% end

end
