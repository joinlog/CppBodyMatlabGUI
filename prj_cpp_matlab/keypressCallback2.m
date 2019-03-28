function keypressCallback2(src,eventdata)
global h_start;
global h_end;
global h_pb;

global h_text_start;
global h_text_end;
global h_text_pb;

global h_rts;
global h_text_rts;

global h_qc;
global h_text_qc;

global h_select_object;
global h_text_select_object;


global mStart;
global mEnd;
global mPB;
global mQC;

key = eventdata.Character;
disp(key);

if key == '1'
    h_select_object = h_start;
elseif key == '2'
    h_select_object = h_end;
end


% w上 s下 a左 d右
key_num = 0;
if key == 'd'
    key_num = 1;
elseif key == 's'
    key_num = 2;
elseif key == 'a'
    key_num = 3;
elseif key == 'w'
    key_num = 4;
end
%disp('key_num=');
%disp(num2str(key_num));
% key_num = str2double(key);
% if (~isempty(key_num))
    if(key_num >= 1 && key_num <= 4)
        if h_select_object == h_start
            mStart(1,1:2) = move_point(mStart(1,1:2), key_num);
            [h_start, h_text_start]= plotNodeAndDirection(mStart(1,1) , mStart(1,2) ,mStart(1,3), mStart(1,4) ,h_start, h_text_start);
            h_select_object = h_start;
        elseif h_select_object == h_end
            mEnd(1,1:2) = move_point(mEnd(1,1:2), key_num);
            [h_end, h_text_end]= plotNodeAndDirection(mEnd(1,1) , mEnd(1,2) ,mEnd(1,3), mEnd(1,4) ,h_end, h_text_end);
            h_select_object = h_end;
        else
            [m,n] = size(h_qc);
            for i = 1 : n 
                if h_select_object == h_qc(i)
                    mQC(i,1:2) = move_point(mQC(i,1:2), key_num);
                    mQC(i,3:4) = move_point(mQC(i,3:4), key_num);
                    if  h_qc(i) ~= 0
                        delete(h_qc(i));
                    end
                    qcx=[mQC(i,1),mQC(i,3)];
                    qcy=[mQC(i,2),mQC(i,4)];
                    h_qc(i) = line(qcx, qcy, 'Color','r');
                    h_select_object = h_qc(i);
                    break;
                end
            end
        end

    end
% end

% 更改方向
if key == 'e'
    if h_select_object == h_start
        mStart(1,3) = changeDirection(mStart(1,3));
        [h_start, h_text_start]= plotNodeAndDirection(mStart(1,1) , mStart(1,2) ,mStart(1,3), mStart(1,4) ,h_start, h_text_start);
        h_select_object = h_start;
    elseif h_select_object == h_end
        mEnd(1,3) = changeDirection(mEnd(1,3));
        [h_end, h_text_end]= plotNodeAndDirection(mEnd(1,1) , mEnd(1,2) ,mEnd(1,3), mEnd(1,4) ,h_end, h_text_end);
        h_select_object = h_end;
    end
end

end
