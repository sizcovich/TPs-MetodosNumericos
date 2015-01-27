function [ V ] = RQ( Ak )
V = eye(784,784);
sumaArriba = 1005;
while sumaArriba >= 1000
    sumaArriba = 0;
    [Qk, Rk] = qr(Ak);
    Ak = Rk*Qk;
    V = V*Qk;
    for i=2:784
        for j=1:i-1
            sumaArriba = sumaArriba + abs(Ak(i,j));
        end
    end
    sumaArriba
end
end

