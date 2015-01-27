function [ U, K ] = TP2automatizado( imagen )
%Funcion TP2
%   Recibe imagen, ruido, funcion y cota. imagen es la matriz de uint8,
%   ruido es el ruido que se le agrega ( 0-255 ), funcion es la funcion que
%   se usa para sacar el ruido y cota es la cota que se usa en la funcion.
%   Se ejecuta 10 veces para los mismos datos (cambia x el random)

    I = double(imagen); %matriz de double entre 0 y 255
    U = zeros(1, 6);
    K = zeros(1, 6);
    %maxi = -30000;
    %valMaxi = 0;
    %for i=1:21

        cota = 5000; %(i-1) * 5000 + 10000;
        for j=1 : 6
           	%n = 0;
            sum1 = 0;
            sum2 = 0;
            %ruidoi = round(10 * j);
            if (j == 1)
                ruidoi = 1;
            else
                if j==2
                    ruidoi = 5;
                else
                    if j == 3
                        ruidoi = 15;
                    else
                        if j == 4
                            ruidoi = 30;
                        else
                            if j == 5
                                ruidoi = 50;
                            else
                                ruidoi = 60;
                            end
                        end
                    end
                end
            end
            
            for rep=1:20
                Y = ruido(I, ruidoi);
                T = img2oct(Y);
                T = f1(T, cota);
                X = oct2img(T);
                n = size(imagen,1);
                for l=1:n
                    for k=1:n
                        if (X(l,k)<0)
                            X(l,k) = 0;
                        else 
                            if(X(l,k)>255)
                                X(l,k) = 255;
                            else
                                X(l,k) = round(X(l,k));
                            end
                        end
                        if (Y(l,k)<0)
                            Y(l,k) = 0;
                        else
                            if(Y(l,k)>255)
                                Y(l,k) = 255;
                            else
                                Y(l,k) = round(Y(l,k));
                            end
                        end
                    end
                end
                px = PSNR(I,X);
                py = PSNR(I,Y);
                sum1 = sum1 + px;
                sum2 =  (px - py) + sum2;
            end
            
            U(1, j) = sum1 / 20;
            K(1, j) = sum2 / 20;
        end
    %end

    %La_cota_con_mejor_promedio = (maxi-1) * 5000 + 1000000
    %Con_un_promedio_de = valMaxi
end