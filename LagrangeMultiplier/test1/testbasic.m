clc; close all; clear

syms p x r y
solve('p*sin(x) = r')
% asin(r/p)

[x,y] = solve('x^2 + x*y + y = 3','x^2 - 4*x + 3 = 0') 



clear;
%% Testing vectorize()
syms  x y
g=exp(x^2)+2*exp(y^2)  
vectorize(g)


