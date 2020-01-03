import cv2 as cv

filename = input("Please enter the filename : ")

#Load the image of Einsein
img = cv.imread(filename);

#Convert the image to grayscale
img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY);

#Save the new grayscale image
[name, ext] = filename.split('.')
new_name = name + "_gray." + ext
cv.imwrite(new_name, img_gray)
