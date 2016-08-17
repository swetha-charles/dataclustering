load c_prior_r_alpha.txt
load m_prior_r_alpha.dat



different = 0;
for i = 1:61
    for j = 1:126
        difference = m_prior_r_alpha(i, j) - c_prior_r_alpha(i, j);
        
        if abs(difference) > 0.01
            fprintf('%e , %e \n', m_prior_r_alpha(i, j),  c_prior_r_alpha(i, j));
            different = different + 1; 
        end
           
    end
end

disp(different);