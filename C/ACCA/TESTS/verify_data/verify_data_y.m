load ORIGINAL/y.dat
load OUTPUT/data_y.txt
NP = size(x);

for i = 1: NP
    if(y(i, 1) ~= data_y(i, 1))
        disp('mismatch col1');
        fprintf('%e, %e\n', data_x(i, 1), y(i, 1));
    end
    if(y(i, 2) ~= data_y(i, 2))
        disp('mismatch col 2');
        fprintf('%e, %e\n', data_y(i, 2), y(i, 2));
    end
    if(y(i, 3) ~= data_y(i, 3))
        disp('mismatch col 3');
        fprintf('%e, %e\n', data_y(i, 3), y(i, 3));
    end
    
end
disp('finished Ys');
