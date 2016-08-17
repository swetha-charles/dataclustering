clear all;
%verify that datapoints in original clusters are moving correctly
load OUTPUT/best_cluster.txt;
load OUTPUT/new_clusters_size_ini.txt;
load OUTPUT/new_clusters_ini.txt;
load OUTPUT/data.txt;
load OUTPUT/orig_clusters.txt;
load OUTPUT/orig_clusters_size.txt;

num_data = size(data, 1);
num_clusters = size(new_clusters_size_ini, 1);

clusters_orig{num_clusters} = 1:num_data:num_data;
clusters_new{num_clusters} = 1:num_data:num_data;
before = 1;

%populate orig clusters
for i = 1:num_clusters
    size_orig = orig_clusters_size(i);
    
    for j = 1: size_orig
        if(j == 1)
            clusters_orig{i} = [orig_clusters(before + j - 1)];
        else 
            clusters_orig{i} = [clusters_orig{i}, orig_clusters(before + j - 1)];
                    
        end 
    end 

    before = before + j;
end

%populate new clusters
for k = 1: num_clusters
   
    clusters_new{k} = new_clusters_ini(k);
       
end 

c_row = 1;


%clusters are now setup, we can start calculating average similarity
for i = 1:num_clusters
    orig_max_size = size(clusters_orig{i}, 2);
    for j = 1:orig_max_size
        %disp(clusters_orig{i});
        dp_index = (clusters_orig{i}(j)) + 1;
        
        c_index = (best_cluster(c_row, 1)+1);
        c_best_cluster = (best_cluster(c_row, 2)+1);
        %disp(c_index);
        
        
        av_cluster = zeros(num_clusters, 1);
            for k = 1:num_clusters
                new_max_size = size(clusters_new{k}, 2);
                sum = 0;

                for l = 1:new_max_size
                    xp_index = clusters_new{k}(l) + 1;
                    correl = calculate_correlation(data,dp_index, xp_index);
                   % fprintf('k: %i, l: %i,xp: %i, correl: %f\n',k,l,xp_index, correl);
                    sum = sum + correl;
                end
                
                
               % fprintf('sum: %f\n', sum);
                 %fprintf('new_size: %i\n', new_max_size);
                 av_cluster(k) = ((sum) / new_max_size);
                % fprintf('max size %i\n', new_max_size);
           
                
                
            end 
         
        
        	[M, I] = max(av_cluster);
            cluster_to_move = I(1, 1);
        
            if(cluster_to_move ~= c_best_cluster)
                 fprintf('Matlab index: %i (i: %i, j:%i) , C index: %i\n', dp_index,i, j, c_index);
                 fprintf('Matlab cluster: %i , C cluster: %i\n\n', cluster_to_move, c_best_cluster);
                
                 disp(av_cluster);
                 
            elseif(cluster_to_move == c_best_cluster)
                
                 %fprintf('\nMatlab index: %i (i: %i, j:%i) , C index: %i\n', dp_index,i, j, c_index);
                 fprintf('Matlab cluster: %i , C cluster: %i\n', cluster_to_move, c_best_cluster);
                 fprintf('Cluster calc OK\n\n');
                % disp( av_cluster);

            end 
         
        %move data_index to new cluster
        clusters_new{cluster_to_move} = [ clusters_new{cluster_to_move}, clusters_orig{i}(j)];
        %disp(clusters_new{cluster_to_move});
        %remove data_index from old cluster (Not really necessary)
        %clusters_orig{i} = (take_out_element(clusters_orig{i}, j));
        c_row = c_row + 1;
     end
     
end 
 


