v_max = 1/2; % [rev/s] alltså 1 varv på 2 sekunder
tn = 2;
a_max = v_max/tn; %max acceleration [rev/s^2] 
T_min = 0.005;
t_delta = 10^-3;

t = [tn];

% solve n with recursion
i=1;
while t(i) >= T_min + i*t_delta
    temp = t(i)-T_min - i*t_delta;
    t = [t temp];
    i=i+1;
end
t = flip(t)
n = length(t)

v = zeros(1,n);
for i=[2:n]
  v(i) = v(i-1) + a_max*(t(i) - t(i-1));
end

plot(t,v)
hold on
plot(t,v,'r*')
hold off