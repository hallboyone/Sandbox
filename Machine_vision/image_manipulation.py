import cv2 as cv
import numpy as np

#Load the images in grayscale
img_1 = cv.imread('camera_man_gray.png', 0);
img_2 = cv.imread('einstein_gray.png', 0);
print(img_1.dtype)
print(img_2.dtype)
print(img_1.shape)
print(img_2.shape)

#==============Image Difference==============
#Compute the difference between the two
img_dif = (img_1-img_2)*(img_1>img_2) + (img_2-img_1)*(img_1<=img_2);

#Save the difference 
cv.imwrite('img_dif.png', img_dif)

#=============Add and filter noise============
#The larger, the more extreme the noise
sigma = 50;

#Create the noise
noise = np.random.normal(0, sigma, img_1.shape)

#Add the noise in
img_1_noise = img_1 + noise;

#Clip to 255 and convert the type to 
img_1_noise.clip(0, 255, out=img_1_noise);

#Save the noisy image
cv.imwrite('img_noise.png', img_1_noise)
