% 9/22/2014
% Seung-Chan Kim @KAIST

clc; close all; clear;
syms t1 t2 t3 t4 t5 t6 a1 a2 a3 a4 a5 a6 d1 d2 d3 d4
% Craig p. 81

disp('Puma Robot : Craig p. 81');


RX4 = rotx(-90/180*pi);
RZ4 = rotz(t4);


RX90p = [   1 0 0 0; 
            0 0 -1 0;
            0 1 0 0;
            0 0 0 1
            ];
RX90n = [   1 0 0 0; 
            0 0 1 0;
            0 -1 0 0;
            0 0 0 1];        
        
T01 = trotz(t1)    
T12 = RX90n  * trotz(t2)
T23 = transl([a2 0 0 ]) * trotz(t3) * transl([0 0 d3 ])
T34 = RX90n * transl([a3 0 0 ]) * trotz(t4) * transl([0 0 d4 ])
T45 = RX90p *  trotz(t5)
T56 = RX90n *  trotz(t6)
disp('------');

T13 = T12 * T23;
T13s = simple(T13)

T36 = T34 * T45 * T56;
T16 = T13 * T36
T06 = T01 * T16;
%T16s = simple(T16)

p  = [T06(1,4); T06(2,4); T06(3,4)];
% ps = simple(p)
% 
% J = jacobian(ps, [t1, t2, t3]);
% Js = simple(J)
% DJ = det(J);
% DJs = simple(DJ)
%Js(:,1)

%% APprox.

T03 = T01 * T12 * T23;
p3  = [T03(1,4); T03(2,4); T03(3,4)];
ps = simple(p3)

J = jacobian(ps, [t1, t2, t3]);
Js = simple(J)
DJ = det(J);
DJs = simple(DJ)


% cos(t1)*(a3*cos(t2 + t3) - d4*sin(t2 + t3) + a2*cos(t2)) - d3*sin(t1)
% sin(t1)*(a3*cos(t2 + t3) - d4*sin(t2 + t3) + a2*cos(t2)) + d3*cos(t1)
%                      - d4*cos(t2 + t3) - a3*sin(t2 + t3) - a2*sin(t2)
       
% --> verified with craig book.

            

% R12 = 
