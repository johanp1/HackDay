fileID = fopen('pcm-house1.xyz', 'r')
sizeA = [3 Inf];
formatSpec = '%f %f %f';
xyz = fscanf(fileID, formatSpec, sizeA);

plot3(xyz(1,:), xyz(2,:), xyz(3,:), '*')