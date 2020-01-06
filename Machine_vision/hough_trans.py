import cv2 as cv
import numpy as np
import math

def houghLines(img):
    #Create 0 array with 180 columns and rows equal to the digonal distance accross the img
    d_max = int(math.sqrt((img.shape[0])**2+(img.shape[1])**2))
    accum = np.zeros((2*d_max, 180), dtype = int)

    #Create and array of thetas to reduce the comutational complexity.
    trig_vals = arr = [[(1-j)*math.cos(math.radians(i)) + j*math.sin(math.radians(i)) for i in range(180)] for j in range(2)] 
    
    for row in range(img.shape[0]):
        for col in range(img.shape[1]):
            if img[row, col]:#If the pixel is part of an edges
                for theta in range(180):
                    d = d_max + int(col * trig_vals[0][theta] - row * trig_vals[1][theta]);
                    accum[d, theta] += 1;
                    pass
                pass
            pass
        pass
    cv.imwrite('lines.png', accum)
    return

#Load the image in grayscale
img = cv.imread('camera_man_gray.png', 0);

#Get the edges from the image
edges = cv.Canny(img, 100, 200);

#cv.imwrite('edges.png', edges);
houghLines(edges);


