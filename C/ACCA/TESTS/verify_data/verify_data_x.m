load ORIGINAL/original_data.txt
load OUTPUT/data.txt
NP = size(original_data);

for i = 1: NP
    if(abs(original_data(i, 1) - data(i, 1)) > 0.01)
        disp('mismatch');
        fprintf('%e, %e\n',original_data(i, 1), data(i, 1));
    end
    if(abs(original_data(i, 2) - data(i, 2)) > 0.01)
        disp('mismatch');
        fprintf('%e, %e\n', original_data(i, 2), data(i, 2));
    end
    if(abs(original_data(i, 3) - data(i, 3)) > 0.01)
        disp('mismatch');
        fprintf('%e, %e\n', original_data(i, 3), data(i, 3));
    end
    
end
disp('finished data');


