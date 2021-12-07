x = randn(104, 1);
T = readtable('AMZN.csv', 'PreserveVariableNames',true);

%first five rows of T and the ‘Low’ and ‘Close’ variables 
%T0 = T(1:5,{'Low','Close'}); 
%T_mat=table2array(T0);

% select 52 data from 2017 and another 52 from 2018 
T1 = T(9:60,{'Close'}); 
T2 = T(61:112,{'Close'}); 
X1 = table2array(T1); 
X2 = table2array(T2);
X1 = normalize(X1);
X2 = normalize(X2);

maxlags = 5;
[c, lags] = xcorr(x, maxlags, 'coeff');