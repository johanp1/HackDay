import numpy as np
from PIL import Image

c = list(range(0, 255)) #needs to be normalized...

m = c
for i in range(1,200):
    m = np.vstack([m, c])
    # or np.concatenate([m, c])
#print(m)

img = Image.fromarray(np.uint8(m), "L")
img.show()

# Save the Numpy array as Image
#image_filename = "opengenus_image.jpeg"
#img.save(image_filename)
