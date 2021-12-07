% Cade Williams & Armando Castillo
% EE-4745 - Project 3

rng(1); % For reproducibility 
n = 5; % Number of points per quadrant 
r1 = sqrt(rand(2*n,1)); % Random radii 
t1 = [pi/2*rand(n,1); (pi/2*rand(n,1)+pi)]; % Random angles for Q1 and Q3 
X1 = [r1.*cos(t1) r1.*sin(t1)]; % Polar-to-Cartesian conversion 
r2 = sqrt(rand(2*n,1)); 
t2 = [pi/2*rand(n,1)+pi/2; (pi/2*rand(n,1)-pi/2)]; % Random angles for Q2 and Q4 
X2 = [r2.*cos(t2) r2.*sin(t2)]; 
X = [X1; X2]; % Predictors 
Y = ones(4*n,1); 
Y(2*n + 1:end) = -1; % Labels

Mdl1 = fitcsvm(X,Y,'KernelFunction','polynomial','Standardize',true);
% Mdl1 = fitcsvm(X,Y,'KernelFunction','polynomial', 'PolynomialOrder', 2,'Standardize',true); 
% Mdl1 = fitcsvm(X,Y,'Standardize',true,'KernelFunction','RBF','KernelScale','auto'); 
% Mdl1 = fitcsvm(X,Y,'ClassNames',[false true],'Standardize',true,'KernelFunction','rbf','BoxConstraint',1);

XTest = [X(2,:); X(3,:); X(17,:); X(18,:)]; 
YTest = [Y(2,:); Y(3,:); Y(17,:); Y(18,:)];
len = length(XTest);
[label1,score1] = predict(Mdl1, XTest);
tab1 = table(YTest(1:len), label1(1:len), score1(1:len, 2),'VariableNames',... 
    {'TrueLabel','PredictedLabel','Score'});

XTest1 = Mdl1.SupportVectors; 
l = length(XTest1); 
[label2,score2] = predict(Mdl1,XTest1); 
YTest1 = label2; 
tab2 = table(YTest1(1:l),label2(1:l),score2(1:l,2),'VariableNames',... 
    {'TrueLabel','PredictedLabel','Score'});

d = 0.02; % Step size of the grid 
[x1Grid,x2Grid] = meshgrid(min(X(:,1)):d:max(X(:,1)),... 
min(X(:,2)):d:max(X(:,2))); 
xGrid = [x1Grid(:),x2Grid(:)]; % The grid 
[~,scores1] = predict(Mdl1,xGrid); % The scores 
figure; 
h(1:2) = gscatter(X(:,1),X(:,2),Y); 
hold on 
h(3) = plot(X(Mdl1.IsSupportVector,1),... 
X(Mdl1.IsSupportVector,2),'ko','MarkerSize',10); 
% Support vectors 
contour(x1Grid,x2Grid,reshape(scores1(:,2),size(x1Grid)),[0 0],'k'); 
% Decision boundary 
title('Scatter Diagram with the Decision Boundary') 
legend({'-1','1','Support Vectors'},'Location','Best'); 
hold off

CVMdl1 = crossval(Mdl1); 
misclass1 = kfoldLoss(CVMdl1); 
