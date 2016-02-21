% June 20, 2013
% implemented for Modal Analysis of General Rotor System lectured by Prof. Lee, Jong-Won
% written by Seung-Chan Kim
% Typical orbits
% for more details : http://awesomeairkick.blogspot.kr/2013/06/typical-orbits.html

clc; clear; close all;
theta=0:0.05:2*pi;

%% Figure 1 - Epitrochoid
% https://en.wikipedia.org/wiki/Epitrochoid

r1 = exp(i*theta);
R = r1;
grad1 = R(2) - R(1);

figure;
Rx = real(R);
Ry = imag(R);

plot(Rx,Ry); hold on
plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 6);
axis equal; grid on;
title('r=e^{j\theta}'); %Epitrochoid

%% Figure 2 - Hypocycloid
% https://en.wikipedia.org/wiki/Hypocycloid

r1 = exp(i*theta);
r2 = exp(i*-1*theta);  % Hypocycloid

R = r1+0.5*r2;
grad1 = R(2) - R(1);

figure;
Rx = real(R); Ry = imag(R);

plot(Rx,Ry); hold on
% plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),5,'r');
adjust_quiver_arrowhead_size(h, 10);
axis equal; grid on;
title('r=e^{j\theta}+0.5*e^{-j\theta}'); %Epitrochoid
axis([-1.7 1.7 -1.5 1.5]);

%% Figure 3 - Limacon & Cardioid
% https://en.wikipedia.org/wiki/Lima%C3%A7on
% http://mathworld.wolfram.com/Limacon.html

r1 = exp(i*theta);
r2 = exp(i*2*theta);  % Hypocycloid

R = r1+0.5*r2;
grad1 = R(2) - R(1);

figure;
Rx = real(R); Ry = imag(R);

plot(Rx,Ry); hold on
% plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 10);
axis equal; grid on;
title('r=e^{j\theta}+ 0.5*e^{2\theta}'); %Epitrochoid
axis([-2 2.5 -2 2]);


%% Figure 4 - Petal Curve
% https://en.wikipedia.org/wiki/Rose_(mathematics)

r1 = exp(i*-1*theta);
r2 = exp(i*2*theta);  % Hypocycloid

R = r1+0.8*r2;
grad1 = R(2) - R(1);

figure;
Rx = real(R); Ry = imag(R);

plot(Rx,Ry); hold on
% plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 10);
axis equal; grid on;
title('r=e^{-j\theta}+ e^{2\theta}'); %Epitrochoid
axis([-2 2.5 -2 2]);


%% Figure 4 - Petal Curve - APPLE

r1 = exp(i*-1*theta);
r2 = exp(i*7*theta);  % Hypocycloid

R = r1+0.9*r2;
grad1 = R(2) - R(1);

figure;
Rx = real(R); Ry = imag(R);

plot(Rx,Ry); hold on
% plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 10);
axis equal; grid on;
title('r=e^{-j1\theta}+ 0.9*e^{7\theta}'); %Epitrochoid
axis([-2 2.5 -2 2]);


%% Figure 5 - Epicycloid & Hypocycloid

r1 = exp(i*1*theta);
r2 = exp(i*-5*theta);  % Hypocycloid

R = r1+0.2*r2;
grad1 = R(2) - R(1);

figure;
Rx = real(R); Ry = imag(R);

plot(Rx,Ry); hold on
% plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 10);
axis equal; grid on;
title('r=e^{j1\theta}+ 0.2*e^{-5\theta}'); %Epitrochoid
axis([-2 2.5 -2 2]);

%% Figure 6 - Epitrochoid & Hypotrotrochoid

r1 = exp(i*1*theta);
r2 = exp(i*8*theta);  

R = r1+0.3*r2;
grad1 = R(2) - R(1);

figure;
Rx = real(R); Ry = imag(R);

plot(Rx,Ry); hold on
% plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 10);
axis equal; grid on;
title('r=e^{j1\theta}+ 0.3*e^{8\theta}'); %Epitrochoid
axis([-2 2.5 -2 2]);

return;
% r2 = exp(i*2*theta);




%r2 = exp(i*8*theta); %Epitrochoid
%R = r1+0.3*r2;
 
%r2 = exp(-i*1.0*theta); %Epitrochoid
R = r1+1*r2;
 

grad1 = R(2) - R(1);






figure;
Rx = real(R);
Ry = imag(R);

plot(Rx,Ry); hold on
plot(Rx(1),Ry(1),'rx'); 

h= quiver(Rx(1),Ry(1), real(grad1), imag(grad1),3,'r');
adjust_quiver_arrowhead_size(h, 6);

axis equal;
grid on;
% axis([-1.5 1.5 -1.5 1.5]);
%  axis([-2 2.5 -2 2]);
% axis([-2 2 -1 1]);
% title('r=e^{j\theta}+0.5e^{-j\theta}');
% title('r=e^{j\theta}+e^{j2\theta}');
%title('r=e^{j\theta}+0.2e^{-j5\theta}'); % Hypocycloid
%title('r=e^{j\theta}+0.3e^{-j8\theta}'); %Hypotrochoid
title('r=e^{j\theta}+0.3e^{j8\theta}'); %Epitrochoid
