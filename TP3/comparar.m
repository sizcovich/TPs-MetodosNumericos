function [ total ] = comparar(TC, Xi)
total = zeros(10000,1);
for j=1:10000
    menorDistancia = 9000000;
    for i=1:10
        distancia = norm((TC(:,i)-Xi(:,j)),2);
        if distancia < menorDistancia
            total(j,1) = i-1;
            menorDistancia = distancia;
        end
    end
end
end

