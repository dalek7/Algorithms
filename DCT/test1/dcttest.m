% 9/16/2014
% http://www.mathworks.co.kr/kr/help/signal/ref/dct.html

clc; clear; close all;
x = (1:100) + 50*cos((1:100)*2*pi/40);


%% DCT
X = dct(x);
[XX,ind] = sort(abs(X),'descend');
% ind :  1     6     2     4     5     7     3     8     9    10 


figure;
subplot(2,1,1);
stem(XX);
subplot(2,1,2);
plot(ind,'o-');

%% Find how many DCT coefficients represent 99% of the energy in a sequence.
i = 1;
while norm(X(ind(1:i)))/norm(X)<0.99
   i = i + 1;
end
Needed = i;

%% Reconstruct the signal and compare to the original.

X(ind(Needed+1:end)) = 0;
xx = idct(X);

figure;
plot([x;xx]')
legend('Original',['Reconstructed, N = ' int2str(Needed)], ...
       'Location','SouthEast')
