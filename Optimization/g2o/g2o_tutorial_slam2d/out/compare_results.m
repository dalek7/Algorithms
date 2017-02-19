clc; clear; close all;

% TODO : Find unique poses !
A = load('out_simEdge_from_before.txt');
Au = unique(A, 'rows');
%B = load('out_poses_after.txt');
B = load('out_simEdge_from_after.txt');
figure;
plot(Au(:, 2), Au(:, 3),'.');
hold on;
plot(B(:, 2), B(:, 3),'.');
legend('before', 'after');