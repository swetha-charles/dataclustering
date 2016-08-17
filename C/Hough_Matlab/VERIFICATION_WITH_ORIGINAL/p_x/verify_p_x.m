load c_p_x.txt
load m_p_x.txt



different = 0;
for i = 1:100
  
        difference = m_p_x(i) - c_p_x(i);
        
        if abs(difference) > 0.01
            fprintf('%e , %e \n', m_p_x(i),  c_p_x(i));
            different = different + 1; 
        end
           
 
end

disp(different);