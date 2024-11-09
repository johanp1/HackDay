steps_per_rev = 2.0*4.0*400.0; % gear-ratio*microsteps*motorns steg
ramp_time = 0.5; % tiden från 0-max-speed

t_on_min = 250*10^-6; % microsekunder
t_off_min = 250*10^-6;
T_min = t_on_min + t_off_min; % minsta step-längd
t = 0:0.01:ramp_time;
v_max = 1/(T_min*steps_per_rev); % (steg/s)/(steg/rev)


fprintf("shortest possible step period: %f\n", T_min)
fprintf("given v_max = %.2f, ramp_time = %.2f\n", v_max, ramp_time)

offset = -ramp_time/2;
alfa = 50; %påhittat
%0.5*(1+((f + offset) .* alfa ./ (1 + abs((f + offset) .* alfa)))); 
v = v_max/2*(1+((t + offset) .* alfa ./ (1 + abs((t + offset) .* alfa)))); 
figure(1)
plot(t, v)

%räkna ut T för en given v:
T = 1./(steps_per_rev*v)
t_off_ramp = T-t_on_min
figure(2)
plot(t, t_off_ramp)