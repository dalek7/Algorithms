
clc; close all; clear;

%A = load('COPLANAR_042314_214759.txt'); %
A = load('COPLANAR_042414_105551.txt'); %


angles = A(1, :);

R_craig = [ A(2, :); A(3, :); A(4, :)];
R_XYZ = [ A(5, :); A(6, :); A(7, :)];
R_XY  = [ A(8, :); A(9, :); A(10, :)];
R_ZYX  = [ A(11, :); A(12, :); A(13, :)];

%dot(R_craig(:, 1), R_craig(:, 2))

O = zeros(3,3);
o = zeros(3,1);
% r=[R_craig(1,1), R_craig(2,1), R_craig(3,1)];

axisMajor = 1;
axisMinor = 0.5;

p = calculateEllipse(0, 0, axisMajor, axisMinor, 0);
p3 = [p  zeros(length(p),1)];
p3T1 = [];
p3T2 = [];
p3T3 = [];

x0 = [-axisMajor 0 0]; x1 = [axisMajor 0 0];
y0 = [0 -axisMinor 0]; y1 = [0 axisMinor 0];

x0_t1 = R_ZYX * x0'; x1_t1 = R_ZYX * x1';
x_t1 = [x0_t1'; x1_t1'];

y0_t1 = R_ZYX * y0'; y1_t1 = R_ZYX * y1';
y_t1 = [y0_t1'; y1_t1'];

x0_t2 = R_XYZ * x0'; x1_t2 = R_XYZ * x1';
x_t2 = [x0_t2'; x1_t2'];

y0_t2 = R_XYZ * y0'; y1_t2 = R_XYZ * y1';
y_t2 = [y0_t2'; y1_t2'];

x0_t3 = R_XY * x0'; x1_t3 = R_XY * x1';
x_t3 = [x0_t3'; x1_t3'];

y0_t3 = R_XY * y0'; y1_t3 = R_XY * y1';
y_t3 = [y0_t3'; y1_t3'];


for i=1:length(p)
    p3t = R_ZYX * p3(i,:)';     p3t = p3t';
    p3T1 = [p3T1; p3t];
    
    p3t = R_XYZ * p3(i,:)';     p3t = p3t';
    p3T2 = [p3T2; p3t];
    
    p3t = R_XY * p3(i,:)';     p3t = p3t';
    p3T3 = [p3T3; p3t];
    
end

bShowXYAxis = 1;

%% Comparison between Shortest angle and non-shortest
figure;

%Ori : ZYX

h1 = quiver3(0,0,0, R_ZYX(1,1), R_ZYX(2,1), R_ZYX(3,1),'r');hold on;
quiver3(0,0,0, R_ZYX(1,2), R_ZYX(2,2), R_ZYX(3,2),'r');
quiver3(0.01,0.01,0.01, R_ZYX(1,3), R_ZYX(2,3), R_ZYX(3,3),'r');

% XYZ
h2 = quiver3(0,0,0, R_XYZ(1,1), R_XYZ(2,1), R_XYZ(3,1),'g');
quiver3(0,0,0, R_XYZ(1,2), R_XYZ(2,2), R_XYZ(3,2),'g');
quiver3(0,0,0, R_XYZ(1,3), R_XYZ(2,3), R_XYZ(3,3),'g');

h3 = quiver3(0,0,0, R_XY(1,1), R_XY(2,1), R_XY(3,1),'b');
quiver3(0,0,0, R_XY(1,2), R_XY(2,2), R_XY(3,2),'b');
quiver3(0,0,0, R_XY(1,3), R_XY(2,3), R_XY(3,3),'b');



% plot3(p3T1(:,1), p3T1(:,2),p3T1(:,3), 'r'), 
% plot3(p3T2(:,1), p3T2(:,2),p3T2(:,3), 'g'), 
% plot3(p3T3(:,1), p3T3(:,2),p3T3(:,3), 'b'), 


legend( [h1 h2 h3], {'R_zR_yR_x', 'R_xR_yR_z', 'R_xR_y'}, -1);

% title(s1);
xlabel('X');
ylabel('Y');
zlabel('Z');
s1 = strcat('Coplanar Condition at \theta_x = ', num2str(angles(1)),',  \theta_y = ', num2str(angles(2)),',  \theta_z = ', num2str(angles(3)));
title(s1);

view(128, 18);

%% Comparison between Shortest angle and non-shortest (ELLIPSE)
figure;

%Ori : ZYX

% quiver3(0,0,0, R_ZYX(1,1), R_ZYX(2,1), R_ZYX(3,1),'r');hold on;
% quiver3(0,0,0, R_ZYX(1,2), R_ZYX(2,2), R_ZYX(3,2),'r');
quiver3(0.01,0.01,0.01, R_ZYX(1,3), R_ZYX(2,3), R_ZYX(3,3),'k', 'LineWidth', 2); hold on

% XYZ
% quiver3(0,0,0, R_XYZ(1,1), R_XYZ(2,1), R_XYZ(3,1),'g');
% quiver3(0,0,0, R_XYZ(1,2), R_XYZ(2,2), R_XYZ(3,2),'g');
quiver3(0,0,0, R_XYZ(1,3), R_XYZ(2,3), R_XYZ(3,3),'k', 'LineWidth', 2);

% quiver3(0,0,0, R_XY(1,1), R_XY(2,1), R_XY(3,1),'b');
% quiver3(0,0,0, R_XY(1,2), R_XY(2,2), R_XY(3,2),'b');
quiver3(0,0,0, R_XY(1,3), R_XY(2,3), R_XY(3,3),'k', 'LineWidth', 2);


h1 = plot3(p3T1(:,1), p3T1(:,2),p3T1(:,3), 'r'), 
h2 = plot3(p3T2(:,1), p3T2(:,2),p3T2(:,3), 'g'), 
h3 = plot3(p3T3(:,1), p3T3(:,2),p3T3(:,3), 'b'), 


plot3(x_t1(:,1), x_t1(:,2), x_t1(:,3), 'r');
plot3(y_t1(:,1), y_t1(:,2), y_t1(:,3), 'r');

plot3(x_t2(:,1), x_t2(:,2), x_t2(:,3), 'g');
plot3(y_t2(:,1), y_t2(:,2), y_t2(:,3), 'g');


plot3(x_t3(:,1), x_t3(:,2), x_t3(:,3), 'b');
plot3(y_t3(:,1), y_t3(:,2), y_t3(:,3), 'b');

legend( [h1 h2 h3], {'R_zR_yR_x', 'R_xR_yR_z', 'R_xR_y'}, -1);

% title(s1);
xlabel('X');
ylabel('Y');
zlabel('Z');
s1 = strcat('Coplanar Condition at \theta_x = ', num2str(angles(1)),',  \theta_y = ', num2str(angles(2)),',  \theta_z = ', num2str(angles(3)));
title(s1);

view(149, 12);

