import cv2 as cv

filename = input("Please enter the filename : ")

#Load the image of Einsein
img = cv.imread(filename);

#If the image could not be opened, prompt the user again
while (img is None):
    filename = input("Filename not found.\nPlease try again : ")
    img = cv.imread(filename);

#Convert the image to grayscale
img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY);

#Create the new filename
[name, ext] = filename.split('.')
new_name = name + "_gray." + ext

#Save the new grayscale image
cv.imwrite(new_name, img_gray)
