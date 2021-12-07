[x, t] = simplefit_dataset; % regression

q = size(x,2);
q1 = floor(q*.9); q2=q-q1;
ind=randperm(q); ind1=ind(1:q1); ind2=ind(q1+(1:q2));
x1=x(:,ind1); t1=t(:,ind1);
x2=x(:,ind2); t2=t(:,ind2);

net = fitnet(20); % regression
net = train(net, x1, t1);
y = net(x2);
[c, cm, ind, per] = confusion(t2, y);
cm = confusionchart(cm);
cm.Title = 'Simple Fit Regression with 10 Hidden Layers';
cm.RowSummary = 'row-normalized';
cm.ColumnSummary = 'column-normalized';