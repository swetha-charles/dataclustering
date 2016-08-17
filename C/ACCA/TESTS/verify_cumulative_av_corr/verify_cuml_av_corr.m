clear all;
load OUTPUT/av_corr.txt;
load OUTPUT/data.txt;

load OUTPUT/orig_clusters.txt;

load OUTPUT/orig_clusters_size.txt;

%cluster 0
c_zero_size = orig_clusters_size(1);
c_one_size = orig_clusters_size(2);
%datapoint in cluster 1
for j = 1:c_one_size
   point_index =  av_corr(j, 1)+1;


   sum = 0;
    
    for i = 1:c_zero_size
        cluster_index = orig_clusters(i)+1;
        cluster_data = data(cluster_index, :)';
    
        correl = calculate_correlation(data, cluster_index,point_index);
       
        sum = sum + correl;
        
    
    end
    sum = sum/c_zero_size;
    fprintf('C: %f, matlab: %f\n', av_corr(j, 2),sum);
    sum = 0;
    
end



