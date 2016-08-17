%find GO's most commmon in this peak

load GO_1 
GO_1 = result;


N_g = length(result);
j = 1;

common_GO_1_name = unique(GO_1(:, 2));
size = length(common_GO_1_name);

common_GO_1_freq = zeros(size, 1);

for i = 1:N_g
    GO = GO_1(i, 2);
    disp(GO);
  
    if( (ismember(GO ,common_GO_1_name) == 1)) 
        [tf, k] = ismember(GO, common_GO_1_name);
        disp('already exists');
        common_GO_1_freq(k) = common_GO_1_freq(k) + 1;
    else 
        common_GO_1_name(j) = GO;
        common_GO_1_freq(j) = 1;
        j = j + 1;
    end
    
    
    
end 

save common_GO_1_name common_GO_1_name  %names of the GO's in peak 1
save common_GO_1_freq common_GO_1_freq %frequencies of the GO's in peak 1


