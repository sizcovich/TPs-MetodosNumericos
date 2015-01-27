function [] = paraCalcularVectores(senal, ruido)
n = size(senal,1);
    M = m(n);
    Y = M * (senal+ruido) * M';
    figure(1);
    imshow(senal+ruido,[0,255])
	f = f2(Y,5000);
    Z = linsolve(M,f); % resuelve M * Z = Y
    Xt = linsolve(M,Z'); % resuelve X * M' = Z => Z' = M * X'
    X = Xt';
    figure(2);
    imshow(X, [ 0, 255 ] )


%z1 = linsolve(Mden, f);
%psnrormenor = PSNRvector(senal,(senal+ruido))
%psnrrecmenor = PSNRvector(senal, z1)
%
%
%f3 = f1(y,10000);
%z3 = linsolve(Mden, f3);
%psnrrecmenormedio = PSNRvector(senal, z3)
%figure(2);
%plot(z3);
%
%fx = f1(y,20000);
%z2 = linsolve(Mden, fx);
%psnrrecmedio = PSNRvector(senal, z2)
%
%
%fl = f1(y,30000);
%z4 = linsolve(Mden, fl);
%
%psnrrecmayor = PSNRvector(senal, z4)

end



