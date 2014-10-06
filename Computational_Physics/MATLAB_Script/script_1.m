format long;

fp1=fopen('../randomz.binary');
Z7=fread(fp1,10000000,'double');
Z5=Z7(1:100000);
Z3=Z7(1:1000);
Moments_Z7=[moment(Z7,1) moment(Z7,2) moment(Z7,3) moment(Z7,4)]
Moments_Z5=[moment(Z5,1) moment(Z5,2) moment(Z5,3) moment(Z5,4)]
Moments_Z3=[moment(Z3,1) moment(Z3,2) moment(Z3,3) moment(Z3,4)]
Z7_d=[Z7(1:9999995) Z7(2:9999996) Z7(3:9999997) Z7(4:9999998) Z7(5:9999999) Z7(6:10000000)];
CorrCoef_M=corrcoef(Z7_d);
CorrCoef_Z7=[CorrCoef_M(1,:)]

fp2=fopen('../schrage.binary');
S7=fread(fp2,10000000,'double');
S5=S7(1:100000);
S3=S7(1:1000);
Moments_S7=[moment(S7,1) moment(S7,2) moment(S7,3) moment(S7,4)]
Moments_S5=[moment(S5,1) moment(S5,2) moment(S5,3) moment(S5,4)]
Moments_S3=[moment(S3,1) moment(S3,2) moment(S3,3) moment(S3,4)]
S7_d=[S7(1:9999995) S7(2:9999996) S7(3:9999997) S7(4:9999998) S7(5:9999999) S7(6:10000000)];
CorrCoef_M=corrcoef(S7_d);
CorrCoef_S7=CorrCoef_M(1,:)
