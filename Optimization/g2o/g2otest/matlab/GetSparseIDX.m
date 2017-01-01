function idxsparse = GetSparseIDX(data_in, nStride)
% Written by Seung-Chan Kim @ Disney Research, Pittsburgh, 2011
% Example:
% idx = 1:size(A, 1);
% idsparse = GetSparseIDX(idx, 4);
% A = A(idxsparse, :);
    
    idxsparse = find( mod(data_in, nStride) ==0); 