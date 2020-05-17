clear all
close all
clc

%% Init
K = 16;
N = 4;
eps = 0.15;

A = 0.6;
B = 0.9;
Q = 7;
H = 2;
F = 4;

u = zeros(K, N);
u(1, :) = [1 9 8 1];
x = zeros(K, N);
x(:, 1) = 1;
p = zeros(1, N + 1);
b = zeros(1, N);
J = zeros(K, 1);
t = 0.172;

for iter = 1 : K
    for i = 2 : (size(x, 2))
        x(iter, i) = x(iter, i - 1) + u(iter, i - 1);
    end
    p(end) = 0;
    for i = N : -1 : 1
        p(i) = x(iter,i) + p(i + 1);
    end
    for i = 1 : length(b)
        b(i) = u(iter, i) + p(i + 1);
    end
    if norm(b) < eps
        break;
    end
    J(iter) = (1/2)*sum(x(iter, 1 : end) .^ 2 + u(iter, :) .^ 2)
    u(iter + 1, :) = u(iter, :) - t * b;
end

%% Plot
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k'];
figure;
for i = 2 : N + 1
    plot(x(1 : iter, i), colors(i - 1));
    hold on;
end
title('Trajectories, direct gradient');

figure;
plot(J(1 : iter));
title('Performance index');