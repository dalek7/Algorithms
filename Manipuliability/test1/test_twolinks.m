% 9/22/2014
% Seung-Chan Kim @KAIST
% based on http://www.cs.cmu.edu/~cga/kdc-06/lecture-2d-kd/matlab-fk-sym.txt

clc; close all; clear;
syms a1 a2 l1 l2

R01 = [ cos(a1), -sin(a1); sin(a1), cos(a1) ]
% [  cos(a1), -sin(a1)]
% [  sin(a1),  cos(a1)]

R12 = [ cos(a2), -sin(a2); sin(a2), cos(a2) ]
% [  cos(a2), -sin(a2)]
% [  sin(a2),  cos(a2)]

R02 = R01*R12
% [  cos(a1)*cos(a2)-sin(a1)*sin(a2), -cos(a1)*sin(a2)-sin(a1)*cos(a2)]
% [  sin(a1)*cos(a2)+cos(a1)*sin(a2),  cos(a1)*cos(a2)-sin(a1)*sin(a2)]
R02 = simple(R02)
% [  cos(a1+a2), -sin(a1+a2)]
% [  sin(a1+a2),  cos(a1+a2)]

link1 = [ l1 ; 0 ]
% [ l1]
% [  0]

link2 = [ l2 ; 0 ]
% [ l2]
% [  0]

% forward kinematics
elbow_location = R01*link1
%[ cos(a1)*l1]
%[ sin(a1)*l1]

wrist_location = elbow_location + R02*link2
% [ cos(a1)*l1+cos(a1+a2)*l2]
% [ sin(a1)*l1+sin(a1+a2)*l2]


% Jacobian
J = jacobian( wrist_location, [ a1 a2 ] )

% [ -sin(a1)*l1-sin(a1+a2)*l2,            -sin(a1+a2)*l2]
% [  cos(a1)*l1+cos(a1+a2)*l2,             cos(a1+a2)*l2]

%det J
DJ = simple(det(J))
% l1*l2*sin(a2)
