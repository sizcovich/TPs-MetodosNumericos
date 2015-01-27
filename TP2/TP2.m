function [  ] = TP2( imagen, ruidoi, cota )
%Funcion TP2
%   Recibe imagen, ruido, funcion y cota. imagen es la matriz de uint8,
%   ruido es el ruido que se le agrega ( 0-255 ), funcion es la funcion que
%   se usa para sacar el ruido y cota es la cota que se usa en la funcion.
%   Se ejecuta 10 veces para los mismos datos (cambia x el random)

    I = double(imagen); %matriz de double entre 0 y 255
    
        Y = ruido(I, ruidoi);
        p = PSNR(I,Y);
        T = img2oct(Y);

        T = f2(T, cota, 10000);

        X = oct2img(T);
        
        %U = [U p];
        n = size(imagen,1);
        for j=1:n
            for k=1:n
                if (X(j,k)<0)
                    X(j,k) = 0;
                end
                if(X(j,k)>255)
                    X(j,k) = 255;
                end
            end
        end
        PSNRdeRestaurada = PSNR(I,X)
        Diferencia = PSNRdeRestaurada-p
        if(PSNRdeRestaurada > 20 && Diferencia > 0)
            %Y = uint8(Y);
            %X = uint8(X);
            imwrite(uint8(Y), 'imgenMasRuido.jpg');
            imwrite(uint8(X), 'imagenRestaurada.jpg');
        end
end