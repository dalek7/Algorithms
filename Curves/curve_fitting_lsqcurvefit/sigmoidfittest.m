% Seung-Chan Kim
% December 14, 2013
% Telerobotics and Control Lab., KAIST
%
% Sigmoid curve fitting in least-squares sense

clc; clear; close all;
A = [
    0.1000    0.5217
    0.2000    0.6250
    0.3000    0.8000
    0.4000    0.8636
    0.5000    0.9474
    0.6000    0.8889
    0.7000    1.0000
    0.8000    1.0000
    0.9000    1.0000
    1.0000    1.0000
    1.1000    1.0000];

xdata = A(:, 1);
ydata = A(:, 2);

%%
%options = optimoptions('lsqcurvefit','Algorithm','levenberg-marquardt');
fun = @(param,xdata)( 1.0 ./ (1 + exp(param(1).*(-xdata + param(2)))));
param = [1 0];

% checking for the size
size(ydata)
size(fun(param,xdata))

param_updated = lsqcurvefit(fun,param,xdata,ydata)

ydata2 = fun(param_updated,xdata);

%xdata3 = min(xdata) : (max(xdata) - min(xdata))/100 : max(xdata);
xdata3 = linspace(xdata(1), xdata(size(xdata,1)));
ydata3 = fun(param_updated,xdata3);

%% Figure
figure;
plot(xdata, ydata, '*');
hold on;
plot(xdata,  ydata2, 'r*');
plot(xdata3, ydata3, '-');
title ('Sigmoid curve fitting');
