load m_p_r_alpha_I_Data.dat %original probabilities from Peter's old data
load original_posterior_p_r_alpha_given_data.txt%reimplimentation's run on data 


different = 0;
for i = 1:61
    for j = 1:126
        difference = m_p_r_alpha_I_Data(i, j) - original_posterior_p_r_alpha_given_data(i, j);
        
        if abs(difference) > 0.0001
            fprintf('%d , %d \n', m_p_r_alpha_I_Data(i, j), original_posterior_p_r_alpha_given_data(i, j));
            different = different + 1; 
        end
           
    end
end

disp(different);
