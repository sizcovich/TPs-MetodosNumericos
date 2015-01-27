function [ entrada ] = f2( entrada, cota)
%QUITARRUIDO Summary of this function goes here
%   Detailed explanation goes here
n = size(entrada, 1);
for i=1 : n
    if abs(entrada(i)) > cota 
        entrada(i) = entrada(i) - 30;
    end
end
end


