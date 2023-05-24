% r is what will be read from lidar
angle_inc = 90/400;
alpha = 0:angle_inc:360-angle_inc; % angle in the horizontal plane
beta = 10;
r = min(abs( 5./(cosd(alpha)*cosd(beta)) ), abs( 4./(sind(alpha)*cosd(beta)) ));

x = r.*cosd(alpha)*cosd(beta);
y = r.*sind(alpha)*cosd(beta);
z = r*sind(beta);
xy = [x' y' z'];
%add z
%plannar_coord = [xy zeros(size(xy,1),1)];

plot3(xy(:,1), xy(:,2), xy(:,3), '*')
hold on
for i = 1:length(r)
    plot3([0 xy(i, 1)], [0 xy(i, 2)], [0 xy(i, 3)])
end

% alpha - vinkeln i horisontalplanet
% beta - vinkeln i vertikalplanet
%
% x = r*cos(alpha)*cos(beta)
% y = r*sin(alpha)*cos(beta)
% z = r*sin(beta)

%enligt det henrik länkade
%x = r * sin(th) * cos(tv)
%y = r * sin(th) * sin(tv)
%z = r * cos(th)