import numpy as np
import math
import matplotlib.pyplot as plt

#from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
from matplotlib import style

ANGLE_INC = 360/1600

alpha = np.arange(0, 360, ANGLE_INC)
BETA = 10

r = []
for a in alpha:
    try:
        r1 = 5/(math.cos(np.rad2deg(a))*math.cos(np.rad2deg(BETA)))
    except ZeroDivisionError:
        r1 = 1000 #something large

    try:
        r2 = 4/(math.sin(np.rad2deg(a))*math.cos(np.rad2deg(BETA)))
    except ZeroDivisionError:
        r2 = 1000 #something large

    r_temp = min(abs(r1), abs(r2))
    r.append(r_temp)

    #str = "r = {:.3f}, alpha = {:.3f}, beta = {:.2f}".format(r_temp, a, BETA)
    #print(str)

