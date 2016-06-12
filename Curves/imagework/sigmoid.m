function a = sigmoid(slope, x, center)
% Seung-Chan Kim
% October 11, 2011
% Disney Research Pittsburgh

a = 1.0 ./ (1 + exp(slope*(-x + center)));