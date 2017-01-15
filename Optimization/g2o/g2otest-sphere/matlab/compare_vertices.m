% For testing optimization of sphere vertices (SE3)
% Seung-Chan Kim
clc; clear; close all;
A = load('../out_vertices_before.txt');
%B = load('../out_vertices_after.txt');
%B = load('../out_vertices_after(fixed_id_0).txt');
B = load('../out_vertices_after_wo_lc.txt');


figure;
plot3(A(:, 1), A(:, 2), A(:, 3),'.');
grid on;
axis equal;
title('sphere vertices (SE3) - before');

figure;
plot3(B(:, 1), B(:, 2), B(:, 3),'.');
grid on;
axis equal;
title('sphere vertices (SE3) - after');

figure;
plot3(A(:, 1), A(:, 2), A(:, 3),'.');  hold on;
plot3(B(:, 1), B(:, 2), B(:, 3),'r.'); 
legend('before', 'after');
xlabel('X');
ylabel('Y');
zlabel('Z');
grid on;
axis equal;