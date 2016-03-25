
function r = ddgcd(a, b)
% Seung-Chan Kim
% Euclidean algorithm
% based on http://en.wikipedia.org/wiki/Euclidean_algorithm
% at Starbucks Adena
% 20140301

    while a ~= b
    
        if a>b
            a = a - b;
        else
            b = b - a;
            
        end
    end
    
    r = a;
    
    


