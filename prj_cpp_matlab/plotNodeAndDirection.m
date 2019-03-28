function [h ,htext] = plotNodeAndDirection(x,y,direc,start_or_end,h ,htext)
direc_str = {'\rightarrow';'\downarrow';'\leftarrow';'\uparrow'};
if h ~= 0
    delete(h);
    h = 0;
    delete(htext);
    htext = 0;
end
if start_or_end == 1
    str = strcat(direc_str{direc},'start');
    h = plot(x,y,'go','markersize',3);
    htext = text(x,y,str);
elseif start_or_end == 2
    str = strcat(direc_str{direc},'end');
    h = plot(x,y,'o','markersize',3);
    htext = text(x,y,str);
else
    str = direc_str{direc};
    h = plot(x,y,'o','markersize',3);
    htext = text(x,y,str);
end
    