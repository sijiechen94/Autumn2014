format long;

fp=fopen('4.txt');
A=fread(fp,16777216,'double');
[N,X]=hist(A,1000);
x=linspace(min(X),max(X),1000);
y=1/sqrt(2*pi)*exp(-0.5*x.*x);
hist(A,1000);hold on;plot(x,y*16777216*(max(X)-min(X))/1000,'g');