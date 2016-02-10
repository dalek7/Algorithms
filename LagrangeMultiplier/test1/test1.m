% 6/11/2014 Seung-Chan Kim
% based on http://www2.math.umd.edu/~jmr/241/lagrange.html
clc; close all; clear;
syms x y z

%% Functions
f=4-x^2-y^2+x^4+y^4
g=exp(x^2)+2*exp(y^2)  

gfun = @(x,y) eval(vectorize(g));
ffun = @(x,y) eval(vectorize(f));

[xx, yy] = meshgrid(-1:.05:1,-1:.05:1);

figure;
surf(xx, yy, ffun(xx, yy)); 
title('f');

figure;
surf(xx, yy, gfun(xx, yy)); 
title('g - constraints');


%% Gradients
gradf=jacobian(f,[x,y,z])
gradg=jacobian(g,[x,y,z])

%% Obtaining critical points

[xfcrit,yfcrit]=solve(gradf(1),gradf(2));
[xfcrit,yfcrit]  
size([xfcrit,yfcrit]) % 9x2

%% values of g at the critical points
% gfun=@(x,y) eval(vectorize(g))
%gfun=inline(vectorize(g))


gfun(xfcrit,yfcrit) 
double(gfun(xfcrit,yfcrit))  %same as above

%% values of f at the critical points
% ffun=@(x,y) eval(vectorize(f))
%ffun(xfcrit(1:3),yfcrit(1:3))
double(ffun(xfcrit(1:3),yfcrit(1:3)))

% The theory of Lagrange multipliers tells us that the extreme values will be found at points where the gradients of f and g are parallel. This will be the case precisely when the cross-product of the gradients of f and g is zero. 

%% Getting the crossproduct
gradcross=cross(gradf,gradg);
lagr=gradcross(3)  % since the gradients of f and g lie in the plane (spanned by i and j)
lagfun = @(x,y) eval(vectorize(lagr));
% gradcross =
% [ 0, 0, 2*x*exp(x^2)*(2*y - 4*y^3) - 4*y*exp(y^2)*(2*x - 4*x^3)]


% [xboundcrit,yboundcrit]=solve(g-4,lagr)


figure;
contour(xx, yy, gfun(xx, yy), [4,4], 'r'); hold on;
%contour(xx, yy, ffun(xx, yy), [4,4], 'b'); 
contour(xx, yy, lagfun(xx, yy), [0,0], 'b'); hold off;

%% Visuzlize

figure;
surf(xx, yy, lagfun(xx, yy)); 
title('lag');


%% Finding solutions
xaxiscrits=solve(subs(g-4,y,0));
[xaxiscrits,[0;0]]

yaxiscrits=solve(subs(g-4,x,0));
[[0;0],yaxiscrits]
double([xaxiscrits,[0;0]])
double([[0;0],yaxiscrits])

%the corresponding f-values are:

double(ffun(xaxiscrits,[0;0]))
double(ffun([0;0],yaxiscrits))


[xb1,yb1]=newton2d(g-4,lagr,.5,.5); [xb1,yb1]
[xb2,yb2]=newton2d(g-4,lagr,-.5,.5); [xb2,yb2]
[xb3,yb3]=newton2d(g-4,lagr,-.5,-.5); [xb3,yb3]
[xb4,yb4]=newton2d(g-4,lagr,.5,-.5) ; [xb4,yb4]

xb = [xb1,xb2,xb3,xb4];
yb = [yb1,yb2,yb3,yb4];
zb = ffun(xb,yb);

figure;
contour(xx, yy, gfun(xx, yy), [4,4], 'k'); hold on;
contour(xx, yy, ffun(xx, yy), [3:.1:4.2]); hold on;
plot(xb, yb, '*');


figure;
surf(xx, yy, ffun(xx, yy)); hold on;
plot3(xb, yb,zb, 'm*', 'LineWidth',2, 'MarkerSize',10);

title('f with solutions highlighted');
return;





genplot(g, -2:.1:2,-2:.1:2,'contour',[4,4],'r'); hold on;
%genplot(lagr, -2:.05:2,-2:.05:2,'contour',[0,0],'b'); hold off;  

