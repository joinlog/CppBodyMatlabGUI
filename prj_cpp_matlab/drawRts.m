function drawRts()
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
global h_rts;
global mRts;
global g_agv_code;
% »­×ÓÂ·¾¶
    [m,n] = size(h_rts);
    
    for i=1:n
        if(h_rts(i) ~= 0)
            delete(h_rts(i));
            h_rts(i) = 0;
        end

    end
    
    agvRtsStart=0;
    agvRtsEnd = 0;
    [m,n]=size(mRts);
    i=0;
    for j = 1:m
        if mRts(j,1)==g_agv_code
            agvRtsEnd = j - 1;
            if agvRtsStart ~= 0 && agvRtsStart <= agvRtsEnd
                %disp(['draw rts']);
                i = i + 1;
                h_rts(i) = line(mRts(agvRtsStart:agvRtsEnd,1), mRts(agvRtsStart:agvRtsEnd,2),  'Color','b');
            end
            agvRtsStart = j + 1;
            continue;
        end
    end
    agvRtsEnd = m;
    if agvRtsStart ~= 0 && agvRtsStart <= agvRtsEnd
        i = i + 1;
        h_rts(i) = line(mRts(agvRtsStart:agvRtsEnd,1), mRts(agvRtsStart:agvRtsEnd,2),  'Color','b');
    end 


end

