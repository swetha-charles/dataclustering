file = fopen('gene_names_1.txt', 'w');
for i = 1:length(gene_names_1)
    fprintf(file, '%s\n', gene_names_1{i});
end