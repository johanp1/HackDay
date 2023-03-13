%function retval = calc_delta_t (input1, input2)
v_max = 1/2; % [rev/s] alltså 1 varv på 2 sekunder
steps_per_rev = 400; % stegmotorspecifik
t_target = 1; % efter t_target [s] vill jag ha v_target (helt påhittad)

% då blir motorstyrsignalen/pulståget:
f = v_max * steps_per_rev;
T_min = 1/f;
fprintf("shortest possible step period: %f\n", T_min)

% acceleration
steps_traveled = steps_per_rev * v_max * t_target;
a_max = v_max/t_target; %max acceleration [rev/s^2] 
fprintf("acceleration = %.2d, given v_max = %.2f, t_target = %.2f\n", a_max, v_max, t_target)
fprintf("steps traveled  %.2f after %.2f s\n", steps_traveled, t_target)

%delta_t beräkningar
%hitta på antal uppdateringar av v under 0:t_target
n = [30:-1:1]; % 30 speed-updates mellan 0 och t_target, help påhittat
sum_n = sum(n);

delta_t = (t_target - n(1)*T_min)/sum_n;
fprintf("delta_t =  %f\n", delta_t)

t = zeros(1,length(n));
t(1) = T_min+n(1)*delta_t;
for i=[2:length(n)]
  t(i) = T_min+n(i)*delta_t + t(i-1);
end

v=[];
v(1) = 0;
for i=[2:length(n)]
  v(i) = v(i-1) + a_max*(t(i) - t(i-1));
end

% det man vill ha ut är delta_t då kan man räkna ut offsett mellan varje
% StartStep:
% T_min+n(i)*delta_t

plot(t,v)
hold on
plot(t,v,'r*')
hold off
%endfunction
