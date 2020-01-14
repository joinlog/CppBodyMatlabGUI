function drawBoxes()
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    global h_agv_boxes;
    global h_text_agv_id;
    global mBoxes;

    global g_try_code;
    global g_clm_code;
    
    % clear agv boxes hanles
    [m,n] = size(h_agv_boxes);
    for i=1:n
        if(h_agv_boxes(i) ~= 0)
            delete(h_agv_boxes(i));
            h_agv_boxes(i) = 0;
        end
    end
    
    % clear agv id text hanles
    [m,n] = size(h_text_agv_id);
    for i=1:n
        if(h_text_agv_id(i) ~= 0)
            delete(h_text_agv_id(i));
            h_text_agv_id(i) = 0;
        end
    end
    
    idxStart=0;
    [m,n]=size(mBoxes);
    i=0;
    for j = 1:m

        if mBoxes(j,1)==g_clm_code 
            idxStart = j + 1;            
        end
        
        if  mBoxes(j,1)==g_try_code 
            %before are claim
            idxEnd = j - 1;
            if idxStart ~= 0 && idxStart <= idxEnd
                for k = idxStart : idxEnd
                    i = i + 1;
                    h_agv_boxes(i) = drawBox(mBoxes(k,:),'b');
                end
            end
        end

    end
    
%     idxEnd = m;
%     if idxStart ~= 0 && idxStart <= idxEnd
%         for k = idxStart : idxEnd
%             i = i + 1;
%             h_agv_boxes(i) = drawBox(mBoxes(k,:),'b');
%         end
%     end 



end

