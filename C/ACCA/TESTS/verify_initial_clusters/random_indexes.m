load OUTPUT/cluster_index.txt;

Np = size(cluster_index, 1);

%%%% check X's %%%%
for i = 0:Np-1
    original = i;
    found = 0;
    
    for j = 1:Np
        new = cluster_index(j);
        difference_x = original - new;
        
        if(abs(difference_x) < 0.001)
           found = 1;
         % fprintf('%i, %i \n', i, new);
        end 
        
    end 
    
    if(found ~= 1)
        fprintf('COULD NOT FIND\n');
        fprintf('%i, %i \n', i,j);
        
    end 
    found = 0;
    
    
end

disp('checking random indexes done');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

