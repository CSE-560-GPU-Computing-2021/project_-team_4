import cv2

def rgb_to_grey(path,outname):
	img = cv2.cvtColor(cv2.imread(path),cv2.COLOR_RGB2GRAY)
	cv2.imwrite(outname,img)

rgb_to_grey("Map3_.png","Map3.png")