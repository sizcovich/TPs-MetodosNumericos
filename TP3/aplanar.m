function [ z ] = aplanar( x )
z = zeros(10000,784);
for k = 1:10000
    for i = 1:28
        for j=1:28
            var = (j+((i-1)*28));
            z(k,var) = x(i,j,k);
        end
    end
end
end