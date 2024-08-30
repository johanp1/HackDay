import numpy as np
from PIL import Image

#from https://stackoverflow.com/questions/60646028/numpy-point-cloud-to-image
def points_to_image(xs, ys, ps, img_size):
    coords = np.stack((ys, xs))
    abs_coords = np.ravel_multi_index(coords, img_size)
    img = np.bincount(abs_coords, weights=ps, minlength=img_size[0]*img_size[1])
    img = img.reshape(img_size)
    return img

"""def points_to_image_torch(xs, ys, ps, sensor_size=(180, 240)):
    xt, yt, pt = torch.from_numpy(xs), torch.from_numpy(ys), torch.from_numpy(ps)
    img = torch.zeros(sensor_size)
    img.index_put_((yt, xt), pt, accumulate=True)
    return img"""

f_in = open('../scans/apa1.xyz','r')

C = np.array([[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0]])
m = np.array([0, 0, 1])
line = f_in.readline()
while line != '':
    if not line.startswith('#'):  
        scan = line.split(' ')

        x = float(scan[0])
        y = float(scan[1])
        z = float(scan[2])

        #when pojecting the point, use the same coordinate system as the image, i.e x - columns, y rows, z- depth
        point3d = np.array([y, z, x, 1])
        point2d = np.matmul(C, point3d)

        if point2d[2] < 0.00001 and point2d[2] > -0.00001:
            print(point2d)
            print(point3d)
            print('\n')

        point2d_coord = point2d/point2d[2]
        point2d_intensity = point2d[2]
        print(point2d_coord)
        m = np.row_stack([point2d_coord, m])

    line = f_in.readline()

#print(m)
#img = Image.fromarray(m, "L")
#img.show()

#points_to_image(apa[0,:], apa[1,:], 1, 500):

        # find max distance and truncate. for normalizing...
"""        if dist > max_dist:
            if dist > 600:
                dist = 600

            max_dist = dist
            max_scan = line

        if h_angle == prev:
            col = 
            
        # is the vertical angle the same as previous
        if v_angle == prev:
            row.append(dist) # yes, append current reading to the image row
        else:
            # the current reading contain a new vertical angle => save the row containing reading with old angle, start new row
            if len(row) > MIN_SCANS_PER_ROW:
                print('vertical angle: ' + str(prev) + ' measurements: ' + str(len(row)))
                
                # if first row, create the matrix
                if len(m) == 0:
                    m = np.resize(row, SCANS_PER_ROW)
                # for all other rows, append/stack
                else:
                    row_resized = np.resize(row, SCANS_PER_ROW)
                    m = np.row_stack([row_resized, m])

            # start new row
            row = [dist]
            prev = v_angle

    line = f_in.readline()

# take care of the last row
if len(row) > MIN_SCANS_PER_ROW:
    print('last line, vertical angle: ' + str(prev) + ' measurements: ' + str(len(row)))
    row_resized = np.resize(row, SCANS_PER_ROW)
    m = np.row_stack([row_resized, m])

print('normalizing...')
print('max dist reading at: ' + max_scan)
m_normalized = (m/max_dist)*255

img = Image.fromarray(np.uint8(m_normalized), "L")
img.show()

image_filename = "scan2"
#img.save(image_filename + '.jpeg')
#img.save(image_filename + '.png')
"""