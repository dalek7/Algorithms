clc; close all; clear;
% craig page 147

l1 = 1;
l2 = 1;
theta1 = -30;
theta1r = theta1 * pi / 180;

theta2 = (10:170);
theta2r = theta2 * pi  / 180;


w = l1 * l2 * sin(theta2r);

c1 = cos(theta1r);
s1 = sin(theta1r);

sc = 0.05;

figure; 
pori = [0 0];
la = [];
sz = size(theta2r);

MH02=[];
MH03=[];
MJ = [];
for i=1:1:sz(2);
    c2 = cos(theta2r(i));
    s2 = sin(theta2r(i));

    T01 = [c1 -s1 0 0 ; s1 c1 0 0 ; 0 0 1 0 ; 0 0 0 1];
    T12 = [c2 -s2 0 l1 ; s2 c2 0 0 ; 0 0 1 0 ; 0 0 0 1];
    T23 = [1 0 0 l2 ; 0 1 0 0 ; 0 0 1 0 ; 0 0 0 1];
    % 
    c12 = cos(theta1r + theta2r(i));
    s12 = sin(theta1r + theta2r(i));

    
    J = [l1*c1+l2*c12, l2 * c12; -l1*s1-l2*s12, -l2*s12];
    MJ = [MJ; J];
   
    
    H02 = T01 * T12;
    H03 = T01 * T12 * T23;
    la1 = sqrt(H03(1,4) *H03(1,4) + H03(2,4)*H03(2,4));
    
    la = [la; la1];
    
    MH02 = [MH02; H02];
    MH03 = [MH03; H03];
    
    link1 = [pori ; H02(1,4), H02(2,4)];
    link2 = [H02(1,4), H02(2,4) ; H03(1,4), H03(2,4)];
    
    plot(link1(:,1), link1(:,2),'LineWidth', 2);hold on;
    plot(link2(:,1), link2(:,2));hold on;
    plot(H02(1,4), H02(2,4),'r+');
    
end




axis equal;
[m, I] = max(w);

pwmax = [MH03(4*I+1, 4), MH03(4*I+2, 4)];
link2max = [H02(1,4), H02(2,4); pwmax(1), pwmax(2)];
h = plot(link2max(:,1), link2max(:,2),'r');hold on;
plot(MH03(4*I+1, 4), MH03(4*I+2, 4),'r+'); 

title('Manipulibility');
% plot(theta2r,w);
grid;
legend(h,'Best posture');

figure;
nj = 10;
ii = 0;
for i=1:nj:sz(2);
    J = MJ( 1+nj*ii*2 : 2+nj*ii*2, :);
    %J = [l1*c1+l2*c12, l2 * c12; -l1*s1-l2*s12, -l2*s12];
    [U,S,V] = svd(J);
    
    H03 = MH03( 1+nj*ii*4 : 4+nj*ii*4, :);
    H02 = MH02( 1+nj*ii*4 : 4+nj*ii*4, :);
    
    la1 = sqrt(H03(1,4) *H03(1,4) + H03(2,4)*H03(2,4));
    
    
    link1 = [pori ; H02(1,4), H02(2,4)];
    link2 = [H02(1,4), H02(2,4) ; H03(1,4), H03(2,4)];
    
    plot(link1(:,1), link1(:,2),'LineWidth', 2);hold on;
    plot(link2(:,1), link2(:,2));hold on;
    plot(H02(1,4), H02(2,4),'r+');
    %plot(H03(1,4), H03(2,4),'o'); 
    
    
    JC = sc*U(:,1)*S(1,1);
    DC = sc*U(:,2)*S(2,2);
    
    %ang = 180*acos(U(1,1))/pi;
    ang = -180*atan2(U(2,1),U(1,1)) / pi;
    
    p = calcEllipse(H03(1,4), H03(2,4), S(1,1)*sc, S(2,2)*sc, ang);
    plot(p(:,1), p(:,2), '-')
    
 
    svdaxisL = [H03(1,4), H03(2,4); H03(1,4)+JC(1,1), H03(2,4)+JC(2,1)];
    plot(svdaxisL(:,1), svdaxisL(:,2),'m');
    svdaxisL = [H03(1,4), H03(2,4); H03(1,4)-JC(1,1), H03(2,4)-JC(2,1)];
    plot(svdaxisL(:,1), svdaxisL(:,2),'m');

    svdaxisL = [H03(1,4), H03(2,4); H03(1,4)+DC(1,1), H03(2,4)+DC(2,1)];
    plot(svdaxisL(:,1), svdaxisL(:,2),'m');
    svdaxisL = [H03(1,4), H03(2,4); H03(1,4)-DC(1,1), H03(2,4)-DC(2,1)];
    plot(svdaxisL(:,1), svdaxisL(:,2),'m');
 

ii = ii+1;
end


%la = 




figure;

plot(la, w', 'o');
hold on;
stem(la(I), w(I),'ro');
xlabel('L_a : distance between the first joint and the hand (end-effector)');
ylabel('Manipulibility');
ttl = num2str(la(I));
ttl = strcat('manipulubility measure : max @ l_a = ', ttl);
title(ttl);
axis equal;
grid;
