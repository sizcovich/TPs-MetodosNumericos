function [ psnr ] = PSNR(x, xmonio)
    n = size(x,1);
    sum = 0;
        for i=1:n
                sum = sum + power((x(i) - xmonio(i)),2);
        end
    sum = sum/(n*n);
    psnr = 10*log10(65025/sum);
end