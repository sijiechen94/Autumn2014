fid=fopen('../output/1.output');
A=fread(fid,[50000,2],'int32');
scatter(A(:,1),A(:,2));