import numpy as np
from PIL import Image

f_in = open('apa.txt','r')

SCANS_PER_ROW = 401
MIN_SCANS_PER_ROW = 300
prev = 0.00
m = []
row = []
max_dist = 0
max_scan = ''

line = f_in.readline()
while line != '':
    if not line.startswith('#'):
        scan = line.split(' ')
        dist = int(scan[2])
        v_angle = float(scan[1])

        # find max distance readibng
        if dist > max_dist:
            max_dist = dist
            max_scan = line

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

#image_filename = "scan"
#img.save(image_filename + '.jpeg')
#img.save(image_filename + '.png')