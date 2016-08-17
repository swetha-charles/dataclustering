load DATA/cluster_0.txt
load OUTPUT/cluster_0_pc.txt

cluster_0 = cluster_0';
pc = corr(cluster_0);

rows = size(pc, 1);
col = size(pc, 2);

for i = 1: rows
    for j = 1:col
        if(abs(pc(i, j) - cluster_0_pc(i, j))>0.001)
            fprintf('incorrect %e, %e\n',pc(i, j), cluster_0_pc(i, j)); 
        end 
        
        
    end 

end 

disp('End');
