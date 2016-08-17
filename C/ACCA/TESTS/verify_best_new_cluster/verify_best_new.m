load OUTPUT/new_clusters.txt;
load OUTPUT/new_clusters_size.txt;
load OUTPUT/data.txt;
load OUTPUT/orig_clusters.txt;
load OUTPUT/orig_clusters_size.txt;
load OUTPUT/best_cluster.txt


data_points = size(best_cluster, 1);
num_clusters = size(new_clusters_size, 1);

           
for dp = 1:data_points
    
     old_data_ind = best_cluster(dp, 1)+1;
     data_point_old = data(old_data_ind, :)';
     
     for c = 1: num_clusters
         new_data_ind = new_clusters(c) + 1;
         data_point_new = (data(new_data_ind, :)');
         
         data_points = [data_point_old, data_point_new];
         correl = corr(data_points);
         results(c) =  correl(2, 1);
         
     end 
                
     [M, I] = max(results);
    if((I(1,1)) ~= ( best_cluster(dp, 2)+1))
        fprintf('WRONG index: %i, matlab max cluster: %i, C max cluster: %i\n',old_data_ind, I(1,1), best_cluster(dp, 2)+1);
    else 
        fprintf('OK index: %i, matlab max cluster: %i, C max cluster: %i\n',old_data_ind, I(1,1), best_cluster(dp, 2)+1);
    end
                      
                
              
         
                
end 
           

       
        
        

