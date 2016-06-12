function y = gaussian(x, m, sig)
% Seung-Chan Kim
% February 15, 2012
% Disney Research Pittsburgh

y = zeros(length(x),1);

for i = 1 : length(x)

    p = -1* (x(i) - m)^2 / (2* sig^2);
    y(i) = exp(p);
end
