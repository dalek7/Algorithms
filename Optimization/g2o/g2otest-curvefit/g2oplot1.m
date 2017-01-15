%Seung-Chan Kim @cafe in Mangpo
clc; clear; close all;
A=load('out_measurements.txt');
params = load('out_params_est.txt');

[Y,I]   = sort(A(:,1));
A       = A(I,:);
%const double& a = params->estimate()(0);
%const double& b = params->estimate()(1);
%const double& lambda = params->estimate()(2)
%double fval = a * exp(-lambda * measurement()(0)) + b;

B = params(1) * exp(-params(3) * A(:,1)) + params(2);
figure;
plot(A(:,1), A(:,2),'.'); hold on;
hold on;
plot(A(:,1), B(:,1),'o-');

grid on;
legend('Observed', 'Estimated');
title('Optimization (g2o in Ubuntu)');



