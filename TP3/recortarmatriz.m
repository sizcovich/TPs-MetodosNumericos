function [ z ] = recortarmatriz( x )
z = zeros(784,10000);
for i=1:10000
    for j=1:784
        z(j,i) = x(j,i);
    end
end
end