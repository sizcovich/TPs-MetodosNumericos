function [ Y ] = img2oct( imagen )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    n = size(imagen,1);
    M = m(n);
    Y = M * imagen * M';
end

