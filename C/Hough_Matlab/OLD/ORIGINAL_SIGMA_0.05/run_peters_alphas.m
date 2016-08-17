load pt_p_alpha_I_Data.dat
ht_alpha = pt_p_alpha_I_Data;

Delta_a = 0.05; 
alpha = -pi/4:Delta_a:7*pi/4;
Delta_r = 0.05; 
r = 0:Delta_r:3;

[alphax,ry] = meshgrid(alpha,r);


figure(2)
plot(alphax(1,:)', ht_alpha);
xlabel('alpha');
title('ht(alpha)');
axis([-pi/4, 7*pi/4, 0, max(ht_alpha)+0.02]);
ax = gca;
%ax.XTick = [-pi/4 pi/2 pi 1.5*pi 2*pi];
%ax.XTickLabel = {'0','\pi/2','\pi','3\pi/2','2\pi'};

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
print pt_p_alpha_I_Data.eps -depsc

