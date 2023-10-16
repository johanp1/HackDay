T_min = 0.001; % snabbast möjliga periodtid för en puls

steps_per_rev = 1600; % ratio*microsteps*motorns steg/varv
% som det är nu, 1600 step/varv, varje varv tar 
v_max = 1/T_min/steps_per_rev; % (steg/s)/(steg/rev)

tn = 0.25; % tid till v_max
a_max = v_max/tn; %max acceleration [rev/s^2] 

t_delta = 0.50*10^-3;

t = [tn];

fprintf("shortest possible step period: %f\n", T_min)
fprintf("acceleration = %.2f, given v_max = %.2f, tn = %.2f\n", a_max, v_max, tn)

% solve n with recursion
i=1;
while t(i) >= T_min + i*t_delta
    temp = t(i)-T_min - i*t_delta;
    t = [t temp];
    i=i+1;
end
t = flip(t);
n = length(t);

fprintf("t_delta set to %f \n", t_delta)
fprintf("number of speed updates during tn, n = %d \n", n)

v = zeros(1,n);
s = zeros(1, n);
for i=[2:n]
  v(i) = v(i-1) + a_max*(t(i) - t(i-1));
  s(i) = s(i-1) + v(i)*(t(i) - t(i-1));
end

plot(t,v)
hold on
plot(t,v,'r*')
hold off