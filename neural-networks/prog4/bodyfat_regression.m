% Cade Williams & Armando Castillo
% Project 4

[x,t] = bodyfat_dataset;

q = size(x,2);
q1 = floor(q*.9); q2=q-q1;
ind=randperm(q); ind1=ind(1:q1); ind2=ind(q1+(1:q2));
x1=x(:,ind1); t1=t(:,ind1);
x2=x(:,ind2); t2=t(:,ind2);

net = fitnet(10);
net = train(net,x1,t1);
view(net)
y = net(x2);
[c, cm, ind, per] = confusion (t2, y);
cm = confusionchart(cm);
cm.Title = 'Bodyfat Regression with 10 Hidden Layers';
cm.RowSummary = 'row-normalized';
cm.ColumnSummary = 'column-normalized';