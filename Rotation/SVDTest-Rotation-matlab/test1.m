
%% July 21, 2013
% Coffee bean, KAIST

%http://nghiaho.com/?page_id=671

%TODO : port this to C++
%http://opencv.willowgarage.com/documentation/cpp/core_operations_on_arrays.html#SVD

clc; close all; clear;

bLoad = 1;


%% Data preparation

if bLoad == 0,

    R = orth(rand(3,3)); % random rotation matrix

    t = rand(3,1); % random translation

    n = 100; % number of points
    A = rand(n,3);
    B = R*A' + repmat(t, 1, n);
    B = B';


    dlmwrite('_A.txt',A)
    dlmwrite('_B.txt',B)
    dlmwrite('_R.txt',R)
    dlmwrite('_t.txt',t)

else
    A = load('_A.txt');
    B = load('_B.txt');
    R = load('_R.txt');
    t = load('_t.txt');
    
    
    n = size(A,1);
    
end


%% Do
%[ret_R, ret_t] = rigid_transform_3D(A, B);

centroid_A = mean(A);
centroid_B = mean(B);
N = size(A,1);  %100

Ac = A - repmat(centroid_A, N, 1);
Bc = B - repmat(centroid_B, N, 1);

% covariance matrix
H = Ac' * Bc;

[U,S,V] = svd(H);

ret_R = V*U';

if det(ret_R) < 0
        disp('Reflection detected');
        V(:,3) = V(:,3) *-1;
        R = V*U';
end

ret_t = -ret_R*centroid_A' + centroid_B';

%% ERROR

A2 = (ret_R*A') + repmat(ret_t, 1, n);
A2 = A2';

err = A2 - B;
err = err .* err;
err = sum(err(:));
rmse = sqrt(err/n)

%disp(sprintf('RMSE: %f', rmse));
disp('If RMSE is near zero, the function is correct!');



%Ra = repmat(centroid_A, N, 1) : 100x3 same as A


%% Plotting
figure;

plot3(A(:,1), A(:,2), A(:,3),'bo');
hold on;
plot3(B(:,1), B(:,2), B(:,3),'rx');


plot3(centroid_A(:,1), centroid_A(:,2), centroid_A(:,3),'b+', 'MarkerFaceColor','b', 'MarkerSize',20, 'LineWidth',2);
plot3(centroid_B(:,1), centroid_B(:,2), centroid_B(:,3),'r+', 'MarkerFaceColor','r', 'MarkerSize',20, 'LineWidth',2);

grid;