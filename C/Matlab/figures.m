p_r_alpha = 'posterior_p_r_alpha_given_data.txt';
p_r_alpha_I_Data = csvread(p_r_alpha);

p_alpha = 'posterior_p_alpha_given_data.txt';
p_alpha_I_Data = csvread(p_alpha);


Delta_a = 0.05; 
alpha = 0:Delta_a:2*pi;
Delta_r = 0.05; 
r = 0:Delta_r:3;

[alphax,ry] = meshgrid(alpha,r);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
contour(alphax, ry, p_r_alpha_I_Data)

axis([0 2*pi 0 3])
ax = gca;
ax.XTick = [0*pi pi/2 pi 1.5*pi 2*pi];
ax.XTickLabel = {'0','\pi/2','\pi','3\pi/2','2\pi'};
ax.YTick = [0 1 2 3];

hold on;



xlabel('alpha');
ylabel('r');
title('p(alpha, r | Data)');
print p_alpha_r_I_Data.eps -depsc

plot([0 0], [0 10], 'k:');
plot([pi/4 pi/4], [0 10], 'k:');
plot([2*pi/4 2*pi/4], [0 10], 'k:');
plot([3*pi/4 3*pi/4], [0 10], 'k:');
plot([4*pi/4 4*pi/4], [0 10], 'k:');
plot([5*pi/4 5*pi/4], [0 10], 'k:');
plot([6*pi/4 6*pi/4], [0 10], 'k:');
plot([7*pi/4 7*pi/4], [0 10], 'k:');
plot([8*pi/4 8*pi/4], [0 10], 'k:');

plot([0 2*pi], [0.5 0.5], 'k:');
plot([0 2*pi], [1 1], 'k:');
plot([0 2*pi], [1.5 1.5], 'k:');
plot([0 2*pi], [2 2], 'k:');
plot([0 2*pi], [2.5 2.5], 'k:');
plot([0 2*pi], [2.5 2.5], 'k:');
%save p_r_alpha_I_Data.dat p_r_alpha_I_Data -ascii;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ht_alpha = sum(p_alpha_I_Data)/(55681);
save p_alpha_I_Data.dat ht_alpha  -ascii;

figure(2)
plot(alphax(1,:)', ht_alpha);
xlabel('alpha');
title('ht(alpha)');
axis([0, 2*pi, 0, max(ht_alpha)+0.02]);
ax = gca;
ax.XTick = [0*pi pi/2 pi 1.5*pi 2*pi];
ax.XTickLabel = {'0','\pi/2','\pi','3\pi/2','2\pi'};

hold on;
plot([0 0], [0 10], 'k:');
plot([pi/4 pi/4], [0 10], 'k:');
plot([2*pi/4 2*pi/4], [0 10], 'k:');
plot([3*pi/4 3*pi/4], [0 10], 'k:');
plot([4*pi/4 4*pi/4], [0 10], 'k:');
plot([5*pi/4 5*pi/4], [0 10], 'k:');
plot([6*pi/4 6*pi/4], [0 10], 'k:');
plot([7*pi/4 7*pi/4], [0 10], 'k:');
plot([8*pi/4 8*pi/4], [0 10], 'k:');

plot([0 2*pi], [0.5 0.5], 'k:');
plot([0 2*pi], [1 1], 'k:');
plot([0 2*pi], [1.5 1.5], 'k:');
plot([0 2*pi], [2 2], 'k:');
plot([0 2*pi], [2.5 2.5], 'k:');
plot([0 2*pi], [2.5 2.5], 'k:');
print p_alpha_I_Data.eps -depsc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(3)
surfl(alphax, ry, p_r_alpha_I_Data)
shading interp;                       
colormap(pink);                 
axis([0 2*pi 0 4 0 0.8])
xlabel('alpha');
ylabel('r');
zlabel('P(alpha,r | Data)');
print p_r_alpha_I_x.eps -depsc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(4)
load mean_data.mat;
plot(X(:, 1), X(:, 2), '.');
title('Data');
print data.eps -depsc


