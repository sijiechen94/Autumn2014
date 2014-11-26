size=192;
time=2400;
fp=fopen('hpp.dat');
A=fread(fp,[size size],'uint8=>uint8');
imwrite(A,'hpp2.gif','gif','DelayTime',0.02);
for i=1:time
A=fread(fp,[size size],'uint8=>uint8');
imwrite(A,'hpp2.gif','gif','WriteMode','append','DelayTime',0.02);
end