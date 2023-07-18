%function retval = calc_delta_t (input1, input2)
v_max = 1/2; % [rev/s] allts� 1 varv p� 2 sekunder
steps_per_rev = 400; % stegmotorspecifik
tn = 1; % efter tn [s] vill jag ha v_target (helt p�hittad)

% d� blir motorstyrsignalen/pulst�get:
f = v_max * steps_per_rev;
T_min = 1/f;
fprintf("shortest possible step period: %f\n", T_min)

% acceleration
a_max = v_max/tn; %max acceleration [rev/s^2] 
fprintf("acceleration = %.2f, given v_max = %.2f, tn = %.2f\n", a_max, v_max, tn)

%delta_t ber�kningar
%hitta p� antal uppdateringar av v under 0:tn
n = 28; % 28 speed-updates mellan 0 och tn, helt p�hittat
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

% det man vill ha ut �r delta_t d� kan man r�kna ut offsett mellan varje
% StartStep:
% T_min+n(i)*delta_t

plot(t,v)
hold on
plot(t,v,'r*')
hold off
%endfunction
