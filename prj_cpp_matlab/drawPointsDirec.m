function drawPointsDirec( )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
global h_start;
global h_end;
global h_pb;

global h_text_start;
global h_text_end;
global h_text_pb;

global mStart;
global mEnd;
global mPB;

[h_start, h_text_start]= plotNodeAndDirection(mStart(1,1) ,mStart(1,2) ,mStart(1,3), mStart(1,4) ,h_start, h_text_start);
[h_end, h_text_end]= plotNodeAndDirection(mEnd(1,1) ,mEnd(1,2) ,mEnd(1,3), mEnd(1,4),h_end, h_text_end);
[h_pb, h_text_pb]= plotNodeAndDirection(mPB(1,1) ,mPB(1,2) ,mPB(1,3), mPB(1,4),h_pb, h_text_pb);

end

