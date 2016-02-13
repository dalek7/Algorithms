
% Linear Algebra : Fibonacci Numbers pp. 301--302
% based on the lecture by Prof. Gilbert Strang
% Seung-Chan Kim @Cafe
% Oct 20th, 2013

clc;close all;clear

A = [1 1 ; 1 0];

[V,D] = eig(A)


V2 = V(1,:) ./V(2,:)
V2 = [V2 ; 1 1];
u0 = [1;0];
u1 = zeros(2,1);


% u1 = A*u0
% u1 = A*u1
% u1 = A*u1

% OR

l1 = V2(1,1);
l2 = V2(1,2);

c1 = 1 / (l1-l2);
c2 = -1 / (l1-l2);

% c = [c1; c2];


u0v = (V2(:,1) - V2(:,2))/(l1-l2);

n = 10;
u1v = zeros(n,2);
u1o = zeros(n,2);

u1o(1,:) = u0;
for i=0:n-1
    
    u1o(i+2,:) = A*u1o(i+1,:)'; %ORIGINAL
    u1v(i+1,:) = (l1^i * V2(:,1) - l2^i * V2(:,2))/(l1-l2); %Using EIG
end

u1o
u1v
plot(u1v(:,1),u1v(:,2),'o')
hold on;
plot(u1v(:,1),u1v(:,2),'rx')
legend('original', 'eig');
