load orig_before.txt;
load orig_before_size.txt;

load orig_after.txt;
load orig_after_size.txt;

load orig_av.txt;
load orig_av_size.txt;

load new.txt;

orig_cluster_no = size(orig_before_size, 1);
sum = 1;

for i = 1: orig_cluster_no
   n_dp = orig_before_size(i);
    
    max_val = max(orig_av((sum: sum + n_dp - 1), :));
    fprintf('max_val: %i\n', max_val);
    
    [tf, index] = ismember(max_val, orig_av((sum: sum + n_dp-1), :));
    fprintf('from: %i , to: %i\n',sum, sum+n_dp-1)
     fprintf('index: %i\n', index+sum-1);
     
        
    if(new(i) ~=  orig_before(index+sum-1))
      fprintf('New cluster wrong');
    else 
      fprintf('New cluster right, %i, %i\n', new(i),orig_before(index+sum-1));
    end
     
    if(orig_after(index+sum-1) ~= -1)
        fprintf('max not taken out\n\n');
    else
        fprintf('%i\n', orig_after(index + sum - 1));
        fprintf('max correctly removed\n\n');
    end
 
    
    sum = sum + n_dp;

end
