load fisheriris
group = species;
rng('default') % For reproducibility
cv = cvpartition(group,'HoldOut',0.40);
trainInds = training(cv);
sampleInds = test(cv);
trainingData = meas(trainInds,:);
sampleData = meas(sampleInds,:);
class = classify(sampleData,trainingData,group(trainInds));
cm = confusionchart(group(sampleInds),class);
