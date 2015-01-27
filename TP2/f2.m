function [ entrada ] = f2( entrada, cota)
%QUITARRUIDO Summary of this function goes here
%   Detailed explanation goes here
    n = size(entrada, 1);
    for j=1:n
        for i=1 : n
            if entrada(i,j) > cota && entrada(i,j) < -cota
                entrada(i,j) = entrada(i,j) - 50;
            end
        end
    end
end


