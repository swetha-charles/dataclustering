load mus_gene_name.mat % all gene , corresponds to mus_GO
load mus_GO.mat % all Gene Ontology markers for mouse gene, corresponds to mus_gene_name 
load gene_names_1.mat % genes in the peak 1


mus_GO = geneassoceasy;

N_g = size(gene_names_1, 2);
N_mg = size(mus_gene_name);
k = 1;
for i = 1:N_g
    disp(i);
    gene = gene_names_1(1, i);
    disp(gene);
    for j = 1:N_mg
        % disp(mus_gene_name(j));
        comparison = strcmp(gene, mus_gene_name(j));
        if(comparison > 0)
            disp('found match!');
            result(k, 1) = gene;
            result(k, 2) = mus_GO(j);
            k = k+1;
        end 
    end
    
    
    
end 


save GO_1 result %Genes in peak 1, and their GO Markers


