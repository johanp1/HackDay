

fileID = fopen('scan_cloud.xyz', 'r')
sizeA = [3 Inf];
formatSpec = '%f %f %f';
xyz = fscanf(fileID, formatSpec, sizeA);

plot3(xyz(1,:), xyz(2,:), xyz(3,:), '*')