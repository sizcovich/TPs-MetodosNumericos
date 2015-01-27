function [ matrix ] = deVectorAMatriz( vector )
matrix = zeros(784,10000);
for j=1:10000
    for i=1:784
    matrix(i,j) = vector(i);
    end
end
end