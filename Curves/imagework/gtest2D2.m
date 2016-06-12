clc;close all; clear;
x = [1:5:400];
y = [1:5:400];
mx = 200;
my = 200;
sig = 30;
g = 100;
lx = length(x);
ly = length(y);

z   = zeros(lx,ly);
dz  = zeros(lx,ly);
for i=1:lx
    for j=1:ly
     z(i,j)   = g*gaussian2D(x(i),y(j), mx,my, sig,sig);      

    end 
    
end


for i=1:lx -1
    for j=1:ly-1
     dz(i,j)   =  dz(i,j);

    end 
    
end


dz = diff(z);
% dy  = diff(y);  dy  = [dy(1); dy];
% 
% % dy = dgaussian(x, m, sig);
% dy = dy / max(dy);
% dy = g*dy;
figure;
grid;
surf(x,y,z);
% hold on;
% plot(x, dy,'r');

% legend('G(x)','dG(x)/dx');
% title('Gaussian & its first order differential function(normalized)');
axis equal;