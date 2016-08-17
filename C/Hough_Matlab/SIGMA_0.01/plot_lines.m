load mean_data.mat %this is a workspace
load indexes.mat
data = X; %name of data
N_x = size(X, 1);
figure(4)
for i = 1:N_x
    if(ismember(i, indexes))
        plot(X(i, 1), X(i, 2), 'r:*');
        hold on;
    else
        plot(X(i, 1), X(i, 2), 'b:.');
        hold on
    end
    
    
    
end

title('Data');
print data.eps -depsc