clc; clear; close all;
A = load('out_data.txt');
plot(A(:, 1), A(:, 2),'.-'); hold on;
plot(A(:, 1), A(:, 3),'.-');
grid on;
legend('Observed', 'Estimated');
title('Optimization (levmar in Android)');