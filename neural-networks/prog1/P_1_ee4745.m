% Cade Williams & Armando Castillo
% Project 1

load fisheriris

% Import data and form matrix
clf
X = meas(:,:);
M = mean(X);

% Standardize data set
PostStd = zeros(150, 4);
sigma = var(X);
for i = 1:150
    PostStd(i,:) = ((X(i,:) - M)./sigma);
end

% Split data into multiple matrices and calculate means
Setosa = X(1:50, 1:4);
Versicolor = X(51:100, 1:4);
Virginica = X(101:150, 1:4);
M1 = mean(Setosa);
M2 = mean(Versicolor);
M3 = mean(Virginica);
M_arr = [M1; M2; M3];

% 2-class LDA
s1 = cov(Setosa);
s2 = cov(Versicolor);
sw = s1+s2;
m = (M1-M2);
sb = m'*m;
sx = sw\sb;
[v1, d1] = eigs(sx);
WOpt = v1(:,1);
y1=WOpt'.*Setosa;
y2=WOpt'.*Versicolor;

% Plot 2-class LDA
figure
hold on
plot(y1(:, 1), y1(:, 2), 'b*', 'LineWidth', 3);
plot(y2(:, 1), y2(:, 2), 'g*', 'LineWidth', 3);
hold off

% Calculate SW
S1 = 0; S2 = 0; S3 = 0;
for i = 1:50
    temp = Setosa(i, 1:4) - M1;
    S1 = S1 +(temp' * temp); 
end
for i = 1:50
    temp = Versicolor(i, 1:4) - M2;
    S2 = S2 +(temp' * temp); 
end
for i = 1:50
    temp = Virginica(i, 1:4) - M3;
    S3 = S3 +(temp' * temp); 
end
SW = S1 + S2 + S3;

% Calculate SB
SB = 0;
for i = 1:3
    temp = M_arr(i, 1:4) - M;
    SB = SB + (50 * (temp' * temp)); 
end

% LDA C-class
SX = SW\SB;
[v2, d2] = eigs(SX);
WCOpt = v2(:, 1:2);
YSet = zeros(50, 2); YVers = zeros(50, 2); YVirg = zeros(50, 2);
for i = 1:50
    YSet(i, 1) = Setosa(i, :) * WCOpt(:, 1);
    YSet(i, 2) = Setosa(i, :) * WCOpt(:, 2);
end
for i = 1:50
    YVers(i, 1) = Versicolor(i, :) * WCOpt(:, 1);
    YVers(i, 2) = Versicolor(i, :) * WCOpt(:, 2);
end
for i = 1:50
    YVirg(i, 1) = Virginica(i, :) * WCOpt(:, 1);
    YVirg(i, 2) = Virginica(i, :) * WCOpt(:, 2);
end

% Plot C-class LDA
figure
hold on
plot(YSet(:, 1), YSet(:, 2), 'b*', 'LineWidth', 3);
plot(YVers(:, 1), YVers(:, 2), 'r*', 'LineWidth', 3);
plot(YVirg(:, 1), YVirg(:, 2), 'g*', 'LineWidth', 3);
hold off

% Find confusion matrix
rng('default');
group = species;
cv = cvpartition(group, 'HoldOut', 0.20);
train = training(cv);
sample = test(cv);
training_data = meas(train,:);
sample_data = meas(sample,:);
class = classify(sample_data, training_data, group(train));
figure
cm = confusionchart(group(sample), class);
