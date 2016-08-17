load OUTPUT/average_correlation.txt;
load OUTPUT/data.txt;

%need to add one to index 

num_new = size(average_correlation, 1);
for i=1:num_new
   
    data_ind = average_correlation(i, 3);
    compare_ind = average_correlation(i, 4);
    av_corr = average_correlation(i, 5);
    
    data_point = data(data_ind + 1, :)';
    compare_point = data(compare_ind + 1, :)';
    
    points = [data_point, compare_point];
    
    correl = corr(points);
    if(abs(correl(2, 1) - av_corr) > 0.0001)
         fprintf('Matlab: %f, C: %f\n',  correl(2, 1), av_corr);
    else 
        fprintf('OK\n');
    
    end 
   
    
    
    
end

