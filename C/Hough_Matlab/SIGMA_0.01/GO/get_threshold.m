load original_posterior_p_alpha_I_Data.dat
load posterior_p_alpha_given_data.txt

Delta_a = 0.05; 
alpha = 0:Delta_a:2*pi;
threshold = 0.25;


%for i = 1:126
   % fprintf('%i, %e, %e\n',i, alpha(i),p_alpha_I_Data(i));
    
%end 
N_x = size(posterior_p_alpha_given_data, 1);
N_a = size(p_alpha_I_Data, 2);

sum_alphas = sum(posterior_p_alpha_given_data, 2);
n = 1;
peaks = [95;48;1];
result = zeros(1);
for i = 1:N_x
    fprintf('%i\n', i);
    for j = 1:3
        peak = peaks(j);
        p_fraction = posterior_p_alpha_given_data(i, peak)/(sum_alphas(i));
   %  disp(p_fraction);
     if(p_fraction > 0.25)
         disp(p_fraction);
         result(n,1) = peak;
         result(n,2) = i;
         result(n,3) = p_fraction;
         n = n + 1;
     end 
    end
end

[values, order] = sort(result(:,1));
sortedmatrix = result(order,:);

save peaks_angles_repeat sortedmatrix

indexes = unique(sortedmatrix(:, 2));
save indexes_repeat indexes
