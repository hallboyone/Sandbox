import cv2 as cv

#Load the image of Einsein
img_1 = cv.imread('camera_man_gray.png', 0);
img_2 = cv.imread('einstein_gray.png', 0);

#Convert the image to grayscale
#img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY);

img_dif = (img_1-img_2)*(img_1>img_2) + (img_2-img_1)*(img_1<=img_2);

cv.imwrite('img_dif.png', img_dif)
