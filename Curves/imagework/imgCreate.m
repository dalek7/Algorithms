% Seung-Chan Kim
% Disney Research Pittsburgh
% October 15, 2011

clc; clear; close all;

w = 512;
h = 512;
A = zeros(w,h, 3);

A(1,1,1) = 1;
for i=1:w
    %v = i  / w;
    %v = sigmoid(0.06, i, w/2);
    v = 0.5*(1 + sin(2*pi*i/w));
    A(:,i,:) = v;
end


% B =  B / max(max(max(B)));

surf(A(:,:,1));
image(A);

imwrite(A, '../../_output/sigmoid2.png', 'PNG');

