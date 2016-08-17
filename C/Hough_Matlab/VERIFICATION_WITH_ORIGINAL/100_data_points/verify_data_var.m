load c_data_var.txt
load m_data_var.txt



different = 0;
for i = 1:100
  
        difference = m_data_var(i, 1) - c_data_var(i, 1);
        
        if abs(difference) > 0.01
            fprintf('%e , %e \n', m_data_var(i, 1),  c_data_var(i, 1));
            different = different + 1; 
        end
           
 
end

disp('x1');
disp(different);

different = 0;
for i = 1:100
  
        difference = m_data_var(i, 2) - c_data_var(i, 2);
        
        if abs(difference) > 0.01
            fprintf('%e , %e \n',  m_data_var(i, 2),  c_data_var(i, 2));
            different = different + 1; 
        end
           
 
end
disp('x2');
disp(different)

different = 0;
for i = 1:100
  
        difference = m_data_var(i, 3) - c_data_var(i, 3);
        
        if abs(difference) > 0.01
            fprintf('%e , %e \n', m_data_var(i, 3),  c_data_var(i, 3));
            different = different + 1; 
        end
           
 
end
disp('var');
disp(different)
