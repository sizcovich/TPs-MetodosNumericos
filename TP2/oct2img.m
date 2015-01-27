function [ X ] = oct2img( Y )
%Cambio de base de OCT a imagen
%   que se yo, estoy re loco
    n = size(Y,1);
    M = m(n);
    Z = linsolve(M,Y); % resuelve M * Z = Y
    Xt = linsolve(M,Z'); % resuelve X * M' = Z => Z' = M * X'
    X = Xt';
    imshow(X, [ 0, 255 ] )
end

