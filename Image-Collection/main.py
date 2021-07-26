####### LIBRARIES #######
import cv2
import os
import time
import subprocess

####### CONSTANTS #######

# Make sure you take the same amount of screenshots
# for each label (example: five images for one, another five for two, ...)
LABELS = ["one", "two", "three", "four", "five"]

IMAGES_FOLDER, LABELS_FOLDER = "images", "collectedimages"
IMAGES_PATH = os.path.join(IMAGES_FOLDER, LABELS_FOLDER)

####### CREATE FOLDERS #######
if not os.path.exists(IMAGES_PATH):
    os.mkdir(IMAGES_FOLDER)
    os.mkdir(IMAGES_PATH)

for label in LABELS:
    label_path = os.path.join(IMAGES_PATH, label)
    if not os.path.exists(label_path): os.mkdir(label_path)

####### TAKE SCREENSHOTS #######
subprocess.Popen(["./build/webcam"] + LABELS)
