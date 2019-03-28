function drawQC()
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

global h_qc;
global h_text_qc;
global mQC;

    [m,n] = size(mQC)
    h_qc = zeros(1,m);
    h_text_qc = zeros(1,m);
    for i = 1 : m
        if  h_qc(i) ~= 0
            delete(h_qc(i));
        end
        qcx=[mQC(i,1),mQC(i,3)];
        qcy=[mQC(i,2),mQC(i,4)];
        h_qc(i) = line(qcx, qcy, 'Color','r');
        h_text_qc = text(mQC(i,3),mQC(i,4),num2str((mQC(i,3) + mQC(i,1)) / 2));
    end

end

