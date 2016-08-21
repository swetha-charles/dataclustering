
total_genes = 55681;

load ('GO1_freq_sorted.mat', 'GO1_freq_sorted');
load ('GO1_name_sorted.mat', 'GO1_name_sorted');

GO_n = length('GO1_name_sorted');

%select only the names from mu_GO and mus_gene_names that were experimented on

load mus_name_GO; %all mouse gene names and it's GO's
load gene_names.mat % genes experimented on, called VarName2
gene_names = VarName2;

k = 1;

G_n = length(gene_names);
for i = 1:G_n
     gene = gene_names(i);
     disp(gene);
    
     for j = 1: length(mus_gene_name)
        
         comparison = strcmp(gene, mus_gene_name(j));
         
         if(comparison > 0)
            disp('found match!');
            exp_gene_name_GO(k, 1) = gene;
            exp_gene_name_GO(k, 2) = mus_GO(i);
            
            exp_gene_name(k, 1) = gene;
            exp_GO(k, 2) = mus_GO(i);
            k = k+1;
        end 
     end
     
     
end 


save exp_gene_name_GO exp_gene_name_GO
save exp_gene_name exp_gene_name 
save exp_GO exp_GO




