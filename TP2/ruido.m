function [ matriz ] = ruido( matriz, ruido )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    n = size(matriz,1); 
    M = rand(n); %matiz con elementos entre 0 y 1
    for i=1:n
        for j=1:n
            matriz(i,j) = matriz(i,j) + round(M(i,j)*randsrc * ruido); %algunos elementos se haran negativos
        end
    end
end

