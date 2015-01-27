function [ res ] = juntarMatrices(X, label)
res = zeros(784,10);
for j=1:10000
    if label(j) == 0
        for i = 1:784
            res(i,1) =  res(i,1) + X(i,j);
        end
    end
    if label(j) == 1
        for i = 1:784
            res(i,2) =  res(i,2) + X(i,j);
        end
    end
    if label(j) == 2
        for i = 1:784
            res(i,3) =  res(i,3) + X(i,j);
        end
    end
    if label(j) == 3
        for i = 1:784
            res(i,4) =  res(i,4) + X(i,j);
        end
    end
    if label(j) == 4
        for i = 1:784
            res(i,5) =  res(i,5) + X(i,j);
        end
    end
    if label(j) == 5
        for i = 1:784
            res(i,6) =  res(i,6) + X(i,j);
        end
    end
    if label(j) == 6
        for i = 1:784
            res(i,7) =  res(i,7) + X(i,j);
        end
    end
    if label(j) == 7
        for i = 1:784
            res(i,8) =  res(i,8) + X(i,j);
        end
    end
    if label(j) == 8
        for i = 1:784
            res(i,9) =  res(i,9) + X(i,j);
        end
    end
    if label(j) == 9
        for i = 1:784
            res(i,10) =  res(i,10) + X(i,j);
        end
    end
    
end

for j=1:10
    if j == 0
        for i=1:784
            res(i,j) = res(i,j)/1001;
        end
    end
    if j == 1
        for i=1:784
            res(i,j) = res(i,j)/1127;
        end
    end
    if j == 2
        for i=1:784
            res(i,j) = res(i,j)/991;
        end
    end
    if j == 3
        for i=1:784
            res(i,j) = res(i,j)/1032;
        end
    end
    if j == 4
        for i=1:784
            res(i,j) = res(i,j)/980;
        end
    end
    if j == 5
        for i=1:784
            res(i,j) = res(i,j)/863;
        end
    end
    
    if j == 6
        for i=1:784
            res(i,j) = res(i,j)/1014;
        end
    end
    if j == 7
        for i=1:784
            res(i,j) = res(i,j)/1070;
        end
    end
    if j == 8
        for i=1:784
            res(i,j) = res(i,j)/944;
            
        end
    end
    if j == 9
        for i=1:784
            res(i,j) = res(i,j)/978;
        end
    end
end
end