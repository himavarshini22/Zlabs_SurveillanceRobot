#!/usr/bin/python3
import time
import os

from picamera2 import Picamera2
from picamera2.encoders import H264Encoder

# Initialize two Picamera2 instances by specifying the camera index
picam1 = Picamera2(camera_num=0)
picam2 = Picamera2(camera_num=1)

# Create and configure video configurations for both cameras
video_config1 = picam1.create_video_configuration(main={"size": (1280, 720), "format": "YUV420"})
video_config2 = picam2.create_video_configuration(main={"size": (1280, 720), "format": "YUV420"})


# Disable autofocus for both configurations
video_config1['controls']['AfMode'] = 0  # Set autofocus mode to manual
video_config2['controls']['AfMode'] = 0  # Set autofocus mode to manual

picam1.configure(video_config1)
picam2.configure(video_config2)

# Create encoders
encoder1 = H264Encoder(10000000)
encoder2 = H264Encoder(10000000)

# Start recording
picam1.start_recording(encoder1, 'test1.h264')
picam2.start_recording(encoder2, 'test2.h264')
time.sleep(30)
picam1.stop_recording()
picam2.stop_recording()

# Remove the previous .mp4 files
os.remove('test1.mp4')
os.remove('test2.mp4')

# Convert .h264 files to .mp4 using ffmpeg
os.system("ffmpeg -fflags +genpts -r 30 -i test1.h264 -c copy test1.mp4")
os.system("ffmpeg -fflags +genpts -r 30 -i test2.h264 -c copy test2.mp4")

# Remove the .h264 files
os.remove('test1.h264')
os.remove('test2.h264')
