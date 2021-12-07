% Cade Williams 
% Quiz 1

% Generate inputs
r = rand(10, 2);
n = sqrt(-2* log(r(:, 1)))*[1, 1].*[cos(2*pi*r(:, 2)), sin(2*pi*r(:, 2))];
X = [r;n];

% PCA
[u, s, v1] = svd(X);
a = u(:, 1:2);
Y_PCA = a'*X;
X1 = a*Y_PCA;

% LDA
m1 = mean(r); m2 = mean(n);
s1 = cov(m1); s2 = cov(m2);
sw = s1 + s2;
sb = (m1 - m2)'*(m1 - m2);
sx = (1/sw) * sb;
[v2, d] = eig(sx);
w = v2(:, 1);
Y1_LDA = w'.*r;
Y2_LDA = w'.*n;

% Print results
disp('PCA RESULT:');
disp(Y_PCA);
disp('LDA RESULTS:')
disp(Y1_LDA);
disp(Y2_LDA);
