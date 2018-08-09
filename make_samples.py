from subprocess import call

import sys
import subprocess
import argparse
import glob

def get_args():
	parser = argparse.ArgumentParser()
	parser.add_argument('-i', dest='image_folder')
	args = parser.parse_args()
	return (args.image_folder)

def make_samples(image_path):
	images = glob.glob(image_path + "/*.png")
	vectors = []

	for img in images:
		vec_path = img.replace(".png", ".vec")
		subprocess.call([ 
			"opencv_createsamples", 
			"-img", img, 
			"-vec", vec_path, 
			"-bg", "bg_plant.lst", 
			"-w", "32", 
			"-h", "32", 
			"-num", "600", 
			"-bgcolor", "0",
			"-bgthresh", "1",
			"-show"
			])
		print("Converted {0} to {1}".format(img, vec_path))
		vectors.append(vec_path)

	# subprocess.call([
	# 	"python mergevec.py",
	# 	"-v", image_path,
	# 	"-o", "combined.vec"
	# ])
	print "done!"

if __name__ == '__main__':
	image_folder = get_args()
	if not image_folder:
		sys.exit('make samples requires an image folder.')

	make_samples(image_folder)