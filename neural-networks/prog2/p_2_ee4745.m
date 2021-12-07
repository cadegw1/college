% Cade Williams & Armando Castillo
% Project 2 - 1 out

% Generate input, output data pairs
N = 100; q = 5;
p = [randn(2, N) randn(2, N) + q]; t = [zeros(1, N)  ones(1, N)];

% plot vectors
figure
hold on
plotpv(p, t);
net = perceptron;
net = configure(net, p, t);

% Split p into 90% design and 10% testing
Q = size(p, 2);
Q1 = floor(Q * 0.90);
Q2 = Q - Q1;
ind = randperm(Q);
ind1 = ind(1:Q1);
ind2 = ind(Q1 + (1:Q2));
P1 = p(:, ind1);
T1 = t(:, ind1);
P2 = p(:, ind2);
T2 = t(:, ind2);
p1 = repmat(con2seq(P1), 1, 1);
t1 = repmat(con2seq(T1), 1, 1);
p2 = repmat(con2seq(P2), 1, 1);
t2 = repmat(con2seq(T2), 1, 1);

% Adapt
net = adapt(net, p1, t1);
plotpc(net.IW{1}, net.b{1});
hold off

% Plot confusion matrix
figure
a = net(P2);
[c, cm, ind, per] = confusion(T2, a);
f1 = confusionchart(cm);
f1.RowSummary = 'row-normalized';
f1.ColumnSummary = 'column-normalized';



