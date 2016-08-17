load ORIGINAL/data.txt
load OUTPUT/cluster_data.txt

clusters = cluster_data;
Np = size(data, 1);

%%%% check X's %%%%
for i = 1:Np
    original = data(i, 1);
    found = 0;
    
    for j = 1:Np
        new_1 = clusters(j, 1);
        difference_x = original - new_1;
        
        if(abs(difference_x) < 1)
           
            new_2 = clusters(j, 2);
            original_2 = data(i, 2);
            difference_2 = original_2 - new_2;
            
            new_3 = clusters(j, 3);
            original_3 = data(i, 3);
            difference_3 = original_3 - new_3;
            
            if((abs(difference_2) < 0.001) && (abs(difference_3) < 0.001))
                %fprintf('%e, %e, %e, %e, %e, %e\n', original, new_1, original_2, new_2, original_3, new_3);
                found = 1;
                break;
            end
            
           
           
        end 
        
    end 
    
    if(found ~= 1)
        disp('COULD NOT FIND');
        fprintf('%i, %i \n', i, j);
        fprintf('%e, %e \n', original, new_1);
        fprintf('%e, %e \n', original_2, new_2);
        fprintf('%e, %e \n\n', original_3, new_3);
    end 
    found = 0;
    
    
end

disp('checking random clusters done');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

