
load OUTPUT/random_indexes.txt

indexes = random_indexes;
Np = size(indexes, 1);

%%%% check X's %%%%
for i = 0:Np-1
    original = i;
    found = 0;
    
    for j = 1:Np
        new = indexes(j);
        difference_x = original - new;
        
        if(abs(difference_x) < 0.001)
           found = 1;
          %fprintf('%i, %i %i\n', i, new, j);
        end 
        
    end 
    
    if(found ~= 1)
        fprintf('COULD NOT FIND\n');
        fprintf('%i, %i \n', i, j);
        
    end 
    found = 0;
    
    
end

disp('checking random clusters done');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

