clc; clear; close all;

A = load('out_measurements.txt');
figure;
plot(A(:, 2), A(:, 3),'.');

