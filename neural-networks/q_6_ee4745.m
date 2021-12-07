% Cade Williams - Quiz 6
X = [1 2 5 6 7].';
y = [-1 -1 1 -1 -1].'; Y = diag(y);
map = @(X)[1 sqrt(2)*X X^2].';
%K = X.*X.';
K = (X.' .* y)^2;
H = Y*K*Y;
A = -Y * X;
B = 0;
f = -ones(5, 1);

x = quadprog(K, f, [], [], y.', B, 0, 50);
w1 = x(1)*y(1)*map(X(1));
w2 = x(2)*y(2)*map(X(2));
w3 = x(3)*y(3)*map(X(3));
w4 = x(4)*y(4)*map(X(4));
w5 = x(5)*y(5)*map(X(5));
wo = w1 + w2 + w3 + w4 + w5;
