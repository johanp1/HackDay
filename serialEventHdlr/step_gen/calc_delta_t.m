%function retval = calc_delta_t (input1, input2)
v_max = 1/2; % [rev/s] alltså 1 varv på 2 sekunder
steps_per_rev = 400; % stegmotorspecifik
tn = 2; % efter tn [s] vill jag ha v_target (helt påhittad)

% då blir motorstyrsignalen/pulståget:
f = v_max * steps_per_rev;
T_min = 1/f;
fprintf("shortest possible step period: %f\n", T_min)

% acceleration
a_max = v_max/tn; %max acceleration [rev/s^2] 
fprintf("acceleration = %.2d, given v_max = %.2f, tn = %.2f\n", a_max, v_max, tn)

%delta_t beräkningar
%hitta på antal uppdateringar av v under 0:tn
n = 40; % 40 speed-updates mellan 0 och tn, helt påhittat
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

% det man vill ha ut är delta_t då kan man räkna ut offsett mellan varje
% StartStep:
% T_min+n(i)*delta_t

plot(t,v)
hold on
plot(t,v,'r*')
hold off
%endfunction
