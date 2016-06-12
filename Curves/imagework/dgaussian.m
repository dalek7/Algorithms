function [y maxval] = dgaussian(x, m, sig)
% Seung-Chan Kim
% February 17, 2012
% Disney Research Pittsburgh

y = zeros(length(x),1);
maxval = +2*exp(-1) /sig ;

for i = 1 : length(x)

    p = -1* (x(i) - m)^2 / (2* sig^2);
    c = -2 *(x(i)-m) / sig^2;
    
    y(i) = c*exp(p);
end
