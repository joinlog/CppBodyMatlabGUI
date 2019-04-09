function ButttonDownFcn2(src,event)
% global h_start;
% global h_end;
% global h_text_start;
% global h_text_end;
% 
% global h_qc;
% global h_text_qc;
% 
% global h_select_object;
% global h_text_select_object;
% 
% 
% pt = get(gca,'CurrentPoint');
% disp([num2str(pt(1,1)), ',', num2str(pt(1,2)) ]);
% if h_text_select_object ~= 0
%     delete(h_text_select_object);
%     h_text_select_object = 0;
% end
% disp('gco');
% %gco
% if abs(gco - h_start) <= 1
%     disp('select start');
%     h_select_object = h_start;
%     h_text_select_object = text(pt(1,1),pt(1,2),'select start');
% elseif abs(gco - h_end) <= 1
%     disp('select end');
%     h_select_object = h_end;
%     h_text_select_object = text(pt(1,1),pt(1,2),'select end');
%     
% else
%     
%     [m,n] = size(h_qc);
%     for i = 1 : n
%         h_qc(i)
%         if abs(gco - h_qc(i)) <= 1
%             disp('select qc');
%             h_select_object = h_qc(i);
%             h_text_select_object = text(pt(1,1),pt(1,2),['select qc ',num2str(i)]);
%             break;
%         end
%     end
% end


end
