function hlz = drawBox(lockzone, mColor)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    j=1;
    hdiagonal=sqrt(power(lockzone(j,3),2) + power(lockzone(j,4),2));
    slopea=atan(lockzone(j,4)./lockzone(j,3));
    i=lockzone(j,5) * pi / 180 - slopea;
    k=lockzone(j,5) * pi / 180 + slopea;
    p1=[lockzone(j,1) + hdiagonal.*cos(i), lockzone(j,2) + hdiagonal.*sin(i)];
    p2=[lockzone(j,1) + hdiagonal.*cos(k), lockzone(j,2) + hdiagonal.*sin(k)];
    p3=[lockzone(j,1) + hdiagonal.*cos(i+pi), lockzone(j,2) + hdiagonal.*sin(i+pi)];
    p4=[lockzone(j,1) + hdiagonal.*cos(k+pi), lockzone(j,2) + hdiagonal.*sin(k+pi)];
    rect=[p1;p2;p3;p4;p1];
    hlz = line(rect(:,1), rect(:,2),  'Color', mColor);
        
end

