load peaks_and_angles.mat
load gene_names.mat;

gene_names = VarName2;%secret name of gene_names :/

N_x = size(sortedmatrix);

for i = 1:N_x
    if(sortedmatrix(i) == 1)
        peak1(i, 1) = sortedmatrix(i, 1);
        peak1(i, 2) = sortedmatrix(i, 2);
        gene_names_1(i) = gene_names(i);
     
             elseif(sortedmatrix(i) == 48)
                 peak48(i, 1) = sortedmatrix(i, 1);
                    peak48(i, 2) = sortedmatrix(i, 2);
                     gene_names_48(i) = gene_names(i);
        
                     elseif(sortedmatrix(i) == 95)
                         peak95(i, 1) = sortedmatrix(i, 1);
                            peak95(i, 2) = sortedmatrix(i, 2);
                              gene_names_95(i) = gene_names(i);
    end
end 

save peak1 peak1;
save gene_names_1 gene_names_1;
save peak48 peak48;
save gene_names_48 gene_names_48;
save peak95 peak95;
save gene_names_95 gene_names_95;

