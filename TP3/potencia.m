function [matriz]=potencia(vector,A,toler)
%
%Power method for computing eigenvalues
%
dd=1;
matriz = zeros(784,784);
n=10;
for i=1:784
while dd> toler
    y=A*vector;
    dd=abs(norm(vector)-n);
    n=norm(vector);
    vector=y/n;
end
value = vector'*A*vector/(vector'*vector);
A = A-(value*(vector*vector'));
for j=1:784
    matriz(j,i) = vector(j,1);
end
end
end