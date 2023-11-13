import numpy as np
import sys
#import open3d as o3d
#import open3d.core as o3c

try:
    input_file_name = sys.argv[1]
except IndexError:
    print('must specify input file')
    sys.exit(2)

f_in = open(input_file_name, 'r')

try:
    output_file_name = sys.argv[2]
except:
    output_file_name = input_file_name.split('.')[0] + '.xyz'

print('saving file as ' + output_file_name)
f_out = open(output_file_name, 'w')

line = f_in.readline()
while line != '':
    if not line.startswith('#'):
        scan = line.split(' ')
        h_angle_rad = np.deg2rad(float(scan[0]))
        v_angle_rad = np.deg2rad(float(scan[1]))
        dist = float(scan[2])

        # alpha - vinkeln i horisontalplanet
        # beta - vinkeln i vertikalplanet
        #
        # x = r*cos(alpha)*cos(beta)
        # y = r*sin(alpha)*cos(beta)
        # z = r*sin(beta)
        x = dist * np.cos(-h_angle_rad) * np.cos(v_angle_rad)
        y = dist * np.sin(-h_angle_rad) * np.cos(v_angle_rad)
        z = dist * np.sin(v_angle_rad)

        f_out.write('{:.6f}'.format(x) + ' ' + '{:.6f}'.format(y) + ' ' + '{:.6f}'.format(z) + '\n')
        #print('{:.6f}'.format(x) + ' ' + '{:.6f}'.format(y) + ' ' + '{:.6f}'.format(z))

    line = f_in.readline()

f_in.close()
f_out.close()
"""
ply_point_cloud = o3d.data.PLYPointCloud()
pcd = o3d.io.read_point_cloud('scan_cloud.xyz')
print(pcd)
o3d.visualization.draw_geometries([pcd],
                                  zoom=0.3412,
                                  front=[0.4257, -0.2125, -0.8795],
                                  lookat=[2.6172, 2.0475, 1.532],
                                  up=[-0.0694, -0.9768, 0.2024])
"""