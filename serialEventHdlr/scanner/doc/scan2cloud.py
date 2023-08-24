import numpy as np

f_in = open('apa.txt','r')
f_out = open('scan_cloud.xyz', 'w')

line = f_in.readline()
while line != '':
    if not line.startswith('#'):
        scan = line.split(' ')
        h_angle = float(scan[0])
        v_angle = float(scan[1])
        dist = int(scan[2])

        # alpha - vinkeln i horisontalplanet
        # beta - vinkeln i vertikalplanet
        #
        # x = r*cos(alpha)*cos(beta)
        # y = r*sin(alpha)*cos(beta)
        # z = r*sin(beta)
        x = dist * np.cos(np.rad2deg(h_angle)) * np.cos(np.rad2deg(v_angle))
        y = dist * np.sin(np.rad2deg(h_angle)) * np.cos(np.rad2deg(v_angle))
        z = dist * np.sin(np.rad2deg(v_angle))

        f_out.write(x + ' ' + y + ' ' + z)
        print(x + ' ' + y + ' ' + z)

f_in.close()
f_out.close()