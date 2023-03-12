## Copyright (C) 2023 johan
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} calc_delta_t (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: johan <johan@HPELITEDESK>
## Created: 2023-03-10

%function retval = calc_delta_t (input1, input2)
v_max = 1/2; % [rev/s] alltså 1 varv på 2 sekunder
steps_per_rev = 400; % stegmotorspecifik
t_target = 2; % efter t_target [s] vill jag ha v_target (helt påhittad)

% då blir motorstyrsignalen/pulståget:
f = v_max * steps_per_rev;
T_min = 1/f;
printf("shortest possible step period: %f\n", T_min)

% acceleration
n_target = steps_per_rev/4; %efter 1/4 varv skall det vara v_target
a_max = v_max/t_target; %max acceleration [rev/s^2] 
printf("acceleration = %.2d, given v_max = %.2f, t_target = %.2f\n", a_max, v_max, t_target)

%delta_t beräkningar
n = [n_target:-1:1];
sum_n = sum(n);

delta_t = (t_target - n_target*T_min)/sum_n;
printf("delta_t =  %f\n", delta_t)

t = [];
t(1) = T_min+n(1)*delta_t;
for i=[2:length(n)]
  t(i) = T_min+n(i)*delta_t + t(i-1);
end

v=[];
v(1) = 0;
for i=[2:length(n)]
  v(i) = v(i-1) + a_max*(t(i) - t(i-1));
end





%endfunction
