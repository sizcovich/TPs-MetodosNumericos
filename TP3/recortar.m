function [ z ] = recortar( x )
z = zeros(10000,1);
    for i=1:10000
        z(i,1) = x(i,1);  
    end
end