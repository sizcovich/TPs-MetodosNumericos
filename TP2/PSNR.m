function [ psnr ] = PSNR(X, Y)
    n = size(X,1);                
    sum = 0;
        for i=1:n
            for j=1:n
                sum = sum + power((X(i,j) - Y(i,j)),2);
            end
        end
    sum = sum/(n*n);
    psnr = 10*log10(65025/sum);
end