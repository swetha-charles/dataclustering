load OUTPUT/new_clusters.txt;
load OUTPUT/new_clusters_size.txt;
load OUTPUT/data.txt;
load OUTPUT/orig_clusters.txt;
load OUTPUT/orig_clusters_size.txt;
load OUTPUT/average_correlation.txt;


%need to add one to index 

num_new = size(new_clusters, 1);
num_old = size(orig_clusters_size, 1);
points_before = 1;

for old = 1:num_old
    size_old = orig_clusters_size(old);
    
    for old_dp = points_before: points_before + size_old -1
      
        data_ind = orig_clusters(old_dp);
        
        if(data_ind >= 0)
            
            data_point_old = (data(data_ind+1, :)');

            for new = 1:num_new
                new_data_ind = new_clusters(new);
                data_point_new = (data(new_data_ind, :)');
                data_points = [data_point_old, data_point_new];
              
                
                correl = corr(data_points);
                fprintf('%f, %f\n',data_ind,  correl(2, 1));
                
            end 
        end 
       
        
        
    end 
   
    points_before = points_before + size_old;
end

