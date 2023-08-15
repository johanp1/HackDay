import numpy as np
from PIL import Image

c = list(range(0, 255)) #needs to be normalized...

f_in = open('apa.txt','r')

line = f_in.readline()
prev = 0.00
m = []
row = []

max_dist = 0

while line != '':
    if not line.startswith('#'):
        scan = line.split(' ')
        dist = int(scan[2])
        v_angle = float(scan[1])

        # find max distance readibng
        if dist > max_dist:
            max_dist = dist

        if v_angle == prev:
            row.append(dist)
        else:
            if len(row) > 300:
                print('vertical angle: ' + str(prev) + ' measurements: ' + str(len(row)))
                
                # if first row, create the matrix
                if len(m) == 0:
                    m = np.resize(row, 400)
                # for all other rows, append/stack
                else:
                    row_resized = np.resize(row, 400)
                    m = np.row_stack([row_resized, m])

            # start new row
            row = [dist]
            prev = v_angle

    line = f_in.readline()

if len(row) > 300:
    print('last line, vertical angle: ' + str(prev) + ' measurements: ' + str(len(row)))
    row_resized = np.resize(row, 400)
    m = np.row_stack([row_resized, m])

# normalize
m_normalized = (m/max_dist)*255

img = Image.fromarray(np.uint8(m_normalized), "L")
img.show()

# Save the Numpy array as Image
#image_filename = "opengenus_image.jpeg"
#img.save(image_filename)
