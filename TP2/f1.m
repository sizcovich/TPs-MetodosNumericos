function [ entrada ] = f1( entrada, cota)
%QUITARRUIDO
    n = size(entrada,1);
    m = size(entrada, 2);
        for i=1 : n
            for j=1:m
                if abs(entrada(i,j)) < cota 
                    entrada(i,j) = 0;
                end
            end
        end
end


