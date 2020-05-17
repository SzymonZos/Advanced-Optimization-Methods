function wynik = minimum_J(t, u, b)
x(1) = 8;
u = u-b*t;
for i=2:6
x(i)=0.9*u(i-1)+x(i-1);
end
wynik = 0;
for i = 1 : 5
wynik = wynik + ((10*(x(i)-4)^2)+u(i)^2);
end
end