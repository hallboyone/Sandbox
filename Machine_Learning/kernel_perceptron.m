%% ========================= Setup Data ========================
%Parameters for labeling the data
M = [3 0; 1, .5];
b = 4;

num_data_points = 10000;

%Generate random data and label each point
all_data = 7*rand(2,num_data_points)-3.5;
all_labels = ones(1,num_data_points);
for i=1:num_data_points
    if(all_data(:,i)'*M*all_data(:,i) - b + .(rand - 0.5) < 0)
        all_labels(i) = -1;
    end
end

%% ====================== Learn Classifier =====================
%Sample the data at random points
num_sample_points = 500;
sample_points_idx = randi(num_data_points, num_sample_points, 1);
samples = all_data(:,sample_points_idx);
labels = all_labels(sample_points_idx);

%Get the alpha array using the perceptron alg with a poly kernal
alpha = perceptronWithKernel(samples, labels);

%Label every data point with learned classifier
learned_labels = ones(1,num_data_points);
for i=1:num_data_points
    x = all_data(:,i);
    y=0;
    
    for m=1:num_sample_points
        y = y + alpha(m) * gaussianKernel(x, samples(:,m));
    end
    
    if(y < 0)
        learned_labels(i) = -1;
    end
end

%% ======================== Plot results =======================
figure 
subplot(1,3,1)
hold on
plot(all_data(1, all_labels==-1), all_data(2, all_labels==-1), 'r*');
plot(all_data(1, all_labels==1), all_data(2, all_labels==1), 'g*');

subplot(1,3,2)
hold on
plot(all_data(1, learned_labels==-1), all_data(2, learned_labels==-1), 'r*');
plot(all_data(1, learned_labels==1), all_data(2, learned_labels==1), 'g*');

subplot(1,3,3)
hold on
plot(all_data(1, learned_labels>all_labels), all_data(2, learned_labels>all_labels), 'gx');
plot(all_data(1, learned_labels<all_labels), all_data(2, learned_labels<all_labels), 'rx');
xlim([-4, 4])
ylim([-4, 4])

%% ========================= Algorithm =========================
%The percepton algorithm using the kernal trick to embbed the data into a
%2nd order poly space
function a = perceptronWithKernel(x, y)
%===================== INIT ========================
m = numel(y);    %number of samples 
G = zeros(m);    %Empty Gram matrix 
a = zeros(1,m);  %Zeros weight array
       
%Fill in Gram matrix 
for i = 1:m 
    for j=1:m
        G(i,j) = gaussianKernel(x(:,i), x(:,j));
    end
end

%====================== RUN ========================
while(true)
    b = a*G;              %Compute beta
    i = find(y.*b<=0, 1); %Find first idx where value negative
    if(isempty(i))        %If no such value exists, break out
        break; 
    else                  %Otherwise, update weight at idx
        a(i) = a(i) + y(i);
    end
end
end

%k'th order poly kernal
function sim = polyKernel(x1, x2, k)
sim = (1+dot(x1,x2)).^k;
end

function sim = gaussianKernel(x1, x2)
sim = exp(-norm(x1-x2)^2/2);
end