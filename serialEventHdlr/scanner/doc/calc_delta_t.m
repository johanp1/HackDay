%function retval = calc_delta_t (input1, input2)

steps_per_rev = 1600; % stegmotorspecifik
%T_min = 2*10^-3 % minsta step-längd
T_min = 1*10^-3 % minsta step-längd

v_max = 1/T_min/steps_per_rev; % (steg/s)/(steg/rev)
tn = 0.25; % efter tn [s] vill jag ha v_target (helt påhittad)

% dï¿½ blir motorstyrsignalen/pulstï¿½get:
fprintf("shortest possible step period: %f\n", T_min)

% acceleration
a_max = v_max/tn; %max acceleration [rev/s^2] 
fprintf("acceleration = %.2f, given v_max = %.2f, tn = %.2f\n", a_max, v_max, tn)

%delta_t berï¿½kningar
%hitta pï¿½ antal uppdateringar av v under 0:tn
n = 28; % 28 speed-updates mellan 0 och tn, helt pï¿½hittat
fprintf("number of speed updates during tn, n = %d \n", n)
sum_n = sum(1:n);

delta_t = (tn - n*T_min)/sum_n;
fprintf("delta_t =  %f\n", delta_t)

t = zeros(1,n);
t(1) = T_min+n*delta_t;
for i=[2:n]
  t(i) = T_min+(n-i+1)*delta_t + t(i-1);
end

v=zeros(1, n);
s=zeros(1, n);
for i = [2:n]
  v(i) = v(i-1) + a_max*(t(i) - t(i-1));
  s(i) = s(i-1) + v(i)*(t(i) - t(i-1));
end

% det man vill ha ut ï¿½r delta_t dï¿½ kan man rï¿½kna ut offsett mellan varje
% StartStep:
% T_min+n(i)*delta_t

plot(t,v)
hold on
plot(t,v,'r*')
hold off
%endfunction
