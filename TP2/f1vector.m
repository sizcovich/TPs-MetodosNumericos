function [ entrada ] = f1( entrada, cota)
%QUITARRUIDO
    n = size(entrada,1);
        for i=1 : n
            if abs(entrada(i)) < cota 
                entrada(i) = 0;
            end
end


