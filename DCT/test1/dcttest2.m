% 9/16/2014
% http://www.mathworks.co.kr/kr/help/signal/ref/dct.html
clc; clear; close all;
x = 50*cos((1:20)*2*pi/40);
xm = -50*cos((1:20)*2*pi/40);

%% DCT
X = dct(x);
Xm = dct(xm);
% ind :  1     6     2     4     5     7     3     8     9    10 

figure;
subplot(2,1,1);
plot(x,'b.-');
hold on;
plot(xm,'r.-');


subplot(2,1,2);
plot(X,'b.-');
hold on;
plot(Xm,'r.-');