
load OUTPUT/cluster_index.txt

indexes = cluster_index;
Np = size(indexes, 1);

%%%% check X's %%%%
for i = 1:Np
    original = i;
    found = 0;
    
    for j = 1:Np
        new = indexes(j);
        difference_x = original - new;
        
        if(abs(difference_x) < 0.001)
           found = 1;
          %fprintf('%i, %i \n', i, j);
        end 
        
    end 
    
    if(found ~= 1)
        fprintf('COULD NOT FIND\n');
        fprintf('%i, %i \n', original, new);
        
    end 
    found = 0;
    
    
end

disp('checking random clusters done');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

