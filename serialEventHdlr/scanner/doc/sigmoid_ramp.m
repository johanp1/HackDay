steps_per_rev = 1600; % ratio*microsteps*motorns steg/varv
ramp_time = 0.5; % ramp-tiden skall vara 1s
T_min = 1*10^-3 % minsta step-längd
t = 0:0.01:ramp_time
v_max = 1/T_min/steps_per_rev; % (steg/s)/(steg/rev)


fprintf("shortest possible step period: %f\n", T_min)
fprintf("given v_max = %.2f, ramp_time = %.2f\n", v_max, ramp_time)

offset = -ramp_time/2;
alfa = 50; %påhittat
%0.5*(1+((f + offset) .* alfa ./ (1 + abs((f + offset) .* alfa)))); 
v = v_max/2*(1+((t + offset) .* alfa ./ (1 + abs((t + offset) .* alfa)))); 
figure(2)
plot(t,v)