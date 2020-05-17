clear all

%% Init
K = 30;
N = 7;
eps = 0.25;

A = 0.6;
B = 0.9;
Q = 7;
H = 2;
F = 4;

u = zeros(K, N);
u(1, :) = [0.1, 0.4, 0.3, 0.5, 0.2, 0.1, 0.2];
x = zeros(K, N + 1);
x(:, 1) = 0.6;
p = zeros(1, N + 1);
b = zeros(1, N);
J = zeros(K, 1);
t = 0.01;

%% Algorithm
for iter = 1 : K
    for i = 2 : size(x, 2)
        x(iter, i) = A * x(iter, i - 1) ^ 2 + B * u(iter, i - 1);
    end
    p(end) = 2 * F * x(end) ^ 3;
    for i = N : -1 : 1
        p(i) = 2 * x(iter,i) * (Q + p(i + 1) * A);
    end
    b_old = b;
    for i = 1 : length(b)
        b(i) = 2 * H * u(iter, i) + B * p(i + 1);
    end
    if iter == 1
        d = -b;
    else
        d = -b + norm(b) ^ 2 / norm(b_old) ^ 2 * d;
    end
    J(iter) = sum(Q * x(iter, 1 : end - 1) .^ 2 + H * u(iter, :) .^ 2) + ...
              F / 2 * x(end) ^ 4;
    if norm(d) < eps
        break;
    end
    u(iter + 1, :) = u(iter, :) + t * d;
end

%% Plot
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k'];
figure;
subplot(1, 2, 1);
for i = 2 : N + 1
    plot(x(1 : iter, i), colors(i - 1));
    hold on;
end
title('Trajectories, conjugated gradient');
hold off;

subplot(1, 2, 2);
plot(J(1 : iter));
title('Performance index, conjugated gradient');