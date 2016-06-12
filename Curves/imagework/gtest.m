clc;close all; clear;
x = [-10:0.1:10];
m = 0;
sig = 2;
g = 1;
y   = g*gaussian(x, m, sig);
dy  = diff(y);  dy  = [dy(1); dy];

% dy = dgaussian(x, m, sig);
dy = dy / max(dy);
dy = g*dy;

dis = ones(size(dy));
lim = 3;
for i=1:length(dy)
   xi = x(i);
   if xi< m - lim*sig || xi> m + lim*sig
       dis(i) = 0;
   else
       dis(i) = g;
   end
end

plot(x,y);
hold on;
plot(x, dy,'r');
plot(x, dis, 'g');
% grid;
legend('S1=G(x)','S2=dS1/dx','S3');
title('Gaussian & its first order differential function(normalized)');
% axis equal;