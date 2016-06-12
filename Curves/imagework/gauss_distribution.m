function f = gauss_distribution(x, mu, s)
% Seung-Chan Kim
% October 12, 2011
% Disney Research Pittsburgh

p1 = -.5 * ((x - mu)/s) .^ 2;
p2 = (s * sqrt(2*pi));
f = exp(p1) ./ p2; 