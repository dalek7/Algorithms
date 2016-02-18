clc; clear; close all;
%rng('default')  % For reproducibility
stream = RandStream('mt19937ar','Seed',5489); % MATLAB's start-up settings

%% Generation
% First generate some simulated data from a mixture of two bivariate
% Gaussian distributions

mu1 = [1 2];
sigma1 = [3 .2; .2 2];
mu2 = [-1 -2];
sigma2 = [2 0; 0 1];
X = [mvnrnd(mu1,sigma1,200);mvnrnd(mu2,sigma2,100)];

scatter(X(:,1),X(:,2),10,'ko')
hold on;
plot(mu1(1), mu1(2),'r+');
plot(mu2(1), mu2(2),'r+');

%% Fit a two-component Gaussian mixture distribution 
options = statset('Display','final');
obj = gmdistribution.fit(X,2,'Options',options);
h = ezcontour(@(x,y)pdf(obj,[x y]),[-8 6],[-8 6]);

title('two-component Gaussian mixture model');

%% Comparison
disp('mu (original) =');
[mu1 ; mu2]
disp('obj.mu=');
obj.mu
disp('obj.Sigma=');
obj.Sigma


