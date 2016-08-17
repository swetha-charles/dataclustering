load ORIGINAL/data.txt
load OUTPUT/pc_sum.txt
load OUTPUT/pc.txt

cluster_0 = data';
pc = corr(cluster_0);

row = size(data, 1);
av_sum = (sum(pc) - 1)/(row - 1);

entries = size(pc_sum, 1);


for i = 1: entries
     if(abs(pc_sum(i) - av_sum(i))>0.001)
            fprintf('incorrect %e, %e\n',pc_sum(i), av_sum(i)); 
     else
          fprintf('correct %e, %e\n',pc_sum(i), av_sum(i)); 
     end 
     
     
end 

disp('End');
