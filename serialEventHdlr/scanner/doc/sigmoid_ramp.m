steps_per_rev = 2.0*4.0*400.0; % gear-ratio*microsteps*motorns steg
ramp_time = 1; %0.5; % tiden fr�n 0-max-speed

t_on_min = 250*10^-6; % microsekunder
t_off_min = 250*10^-6;
T_min = t_on_min + t_off_min; % minsta step-l�ngd
t = 0:0.01:ramp_time;
v_max = 1/(T_min*steps_per_rev); % (steg/s)/(steg/rev) => rev/s
f_max = 1/T_min;

fprintf("shortest possible step period: %f\n", T_min)
fprintf("given v_max = %.2f, ramp_time = %.2f\n", v_max, ramp_time)

offset = -ramp_time/2;
alfa = 50; %p�hittat
%0.5*(1+((f + offset) .* alfa ./ (1 + abs((f + offset) .* alfa)))); 
v = v_max/2.*(1+((t + offset) .* alfa ./ (1 + abs((t + offset) .* alfa)))); 
f = f_max/2.*(1+((t + offset) .* alfa ./ (1 + abs((t + offset) .* alfa)))); 

f_min = f_max/2 * (1 + (offset * alfa / (1 + abs(offset * alfa))))
 
figure(1)
plot(t, v)
ylabel("v")
xlabel("t")

%r�kna ut T (periodtid f�r en puls) givet v:
T = 1./(steps_per_rev*v);
T_f = 1./f;

%r�kna ut t_off
t_off = T-t_on_min;
figure(2)
plot(t, t_off)
ylabel("t-off-ramp")
xlabel("t")
