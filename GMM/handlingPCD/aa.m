% A part of hand recognition from 3-D pointcloud data streams
% Seung-Chan Kim
% August 5, 2014
% http://vlm1.uta.edu/~athitsos/courses/cse6367_spring2011/lectures/11_pca/pca.pdf
% http://www.mathworks.com/matlabcentral/fileexchange/24322-principal-component-analysis--pca--in-matlab/content/pca.m

clc; close all; clear;

A = loadpcd('cloud_cluster_1407254031.pcd');
B = loadpcd('cloud_cluster_all_1407254031.pcd');
A = A';
B = B';

xb = B(:,1);
yb = B(:,2);


z = -A(:,3);
zb = -B(:,3);

mz = mean(z);
mzb = mean(zb);

z2 = mz * ones(length(A),1);

x = A(:,1);
y = A(:,2);

xmean=mean(x);
ymean=mean(y);
numdata = length(A);
xnew=x-xmean*ones(numdata,1);
ynew=y-ymean*ones(numdata,1);

%step 3, covariance matrix
covariancematrix=cov(xnew,ynew);
%step 4, Finding Eigenvectors
[V,D]   = eig(covariancematrix)
D       = diag(D);
maxeigval=V(:,D==max(D))

Dnorm   = D / max(D);

%maxeigval=V(:,find(D==max(D)));

%step 5, Deriving the new data set
%finding the projection onto the eigenvectors

XY = [xnew,ynew];
finaldata=maxeigval'*XY';

%plot([x1 x2],[y1 y2]);
VV1 = Dnorm(1) * V(:,1);
VV2 = Dnorm(2) * V(:,2);


%%  Plot PCA 
figure;
%stem(finaldata, 'DisplayName', 'finaldata', 'YDataSource', 'finaldata');
stem(finaldata);
grid on;
%plot(finaldata);
title('PCA 1D output ')

%%  debug
figure;
l = length(finaldata);
stem3( xnew, ynew, finaldata,'bo');
xlabel('x'); ylabel('y'); zlabel('z');
grid on;

%%  Classification
figure;
title('Final Classification')
hold on
dispx = xnew;
dispy = ynew;

for i=1:size(finaldata,2)
    if  finaldata(i)>=0
        plot(dispx(i),dispy(i),'o')
        plot(dispx(i),dispy(i),'r*')
        
    else
        plot(dispx(i),dispy(i),'o')
        plot(dispx(i),dispy(i),'g*')
    end
    
end

plot([0 Dnorm(1)*V(1,1)],[0 Dnorm(1)*V(1,2)],'k-', 'LineWidth', 2);
plot([0 Dnorm(2)*V(2,1)],[0 Dnorm(2)*V(2,2)],'r-', 'LineWidth', 2);
axis equal;


%% figure


figure;
plot(xnew, ynew, 'b.');
grid on;
xlabel('x'); ylabel('y');

hold on;
O = zeros(size(V(:,1)));

P1 = [O'; V(:,1)'];
P2 = [O'; V(:,2)'];

plot(P1(:,1),P1(:,2), 'g-', 'LineWidth', 2);
plot(P2(:,1),P2(:,2), 'r-', 'LineWidth', 2);


% plot([0 Dnorm(1)*V(1,1)],[0 Dnorm(1)*V(1,2)],'g-', 'LineWidth', 2);
% plot([0 Dnorm(2)*V(2,1)],[0 Dnorm(2)*V(2,2)],'r-', 'LineWidth', 2);
% plot(P,'o-');
axis equal;

%% figure : all data set
figure;
plot3(xb, yb, zb,'.');
grid on;
xlabel('x'); ylabel('y'); zlabel('z');

return;

figure;
plot3(x, y, z,'.');
hold on;
plot3(x, y, z2,'r.');
grid on;
xlabel('x'); ylabel('y'); zlabel('z');

return;

