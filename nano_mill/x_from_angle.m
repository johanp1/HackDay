a = 40; % [mm]
b = 20; % [mm]
alfa=[];
c = [20:0.5:60];

for i = 1:length(c)
  alfa = [alfa acosd( (c(i)^2+b^2-a^2)/(2*b*c(i)) )];
end
plot(c, alfa)

