clc; clear; close all;

w = 512;
h = 512;
A = zeros(w,h, 3);

A(1,1,1) = 1;
% for i=1:w
%     %v = i  / w;
%     v = sigmoid(0.06, i, w/2);
%     A(:,i,:) = v;
% end

B = A;
Ap  =  [0: w-1];
for i=1:w
    %A(i,:,1)
    r= gauss_distribution(Ap, w/2, w/10.0);
    B(i ,:,1) = r;
    B(i ,:,2) = r;
    B(i ,:,3) = r;
    
%     B(i,i,:) = r;
end

B =  B / max(max(max(B)));
% surf(B(:,:,1))
% image(B);
imwrite(B, '../../_output/gaussian.png', 'PNG');


C = B;
x = [1:w];
m= w/2;
sig = w/10.0;
g = 512;
y   = 512-g*gaussian(x, m, sig);

dis = ones(size(y));
lim = 2.5;
for i=1:length(y)
   xi = x(i);
   if xi< m - lim*sig || xi> m + lim*sig
       dis(i) = g-0;
   else
       dis(i) = g-g;
   end
end




image(C);
return;
hold on;
plot(x,y,'r');
plot(x,dis,'b');
legend('S1','S3');
% axis([0 w -5 h+5])


