clc; close all; clear;
syms t1 t2 t3 t4;

% Yaw-Roll-Pitch-Yaw Z-X-Y-Z

R01 = 

R4 = rotz(t4);
R3 = rotx(t3);
R2 = roty(t2);
R1 = rotz(t1);


