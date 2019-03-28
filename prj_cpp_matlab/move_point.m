function point = move_point(point, direc)
step = 50;
direc = mod(direc - 1, 4) + 1;
if direc == 1
    point(1) = point(1) + step;
elseif direc == 2
    point(2) = point(2) - step;
elseif direc == 3
    point(1) = point(1) - step;
elseif direc == 4
    point(2) = point(2) + step;
end