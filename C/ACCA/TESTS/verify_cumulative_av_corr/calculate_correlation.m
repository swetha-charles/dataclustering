function correlation = calculate_correlation(data, dp_index, xp_index)

 xp = data(xp_index, :)';
 dp = data(dp_index, :)';
 
 datapoints = [xp, dp];
 correl = corr(datapoints);
 correlation = correl(2, 1);

