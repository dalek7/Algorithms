% Seung-Chan Kim
% based on http://stackoverflow.com/a/32486205
clc; clear; close all;

v = [1;0;1];
k = [0;0;1];
theta = pi/4;
vrot = v*cos(theta) + cross(k,v)*sin(theta) + k*(k.'*v)*(1-cos(theta));

disp(vrot);

%%
rotationVector = pi/2 * [0, 0, 1];
rotationMatrix = rotationVectorToMatrix(rotationVector);



% vrrotvec2mat