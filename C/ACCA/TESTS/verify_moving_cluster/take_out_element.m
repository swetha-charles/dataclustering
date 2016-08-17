function B = take_out_element(A,i)

% take out element with index i from row array A
B = [A(1:i-1), A(i+1:end)];


