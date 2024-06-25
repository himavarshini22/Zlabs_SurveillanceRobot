import pandas as pd 
import datetime
import serial 
import time 
import os
import zipfile
from picamera2 import Picamera2
from picamera2.encoders import H264Encoder


class Timer:
    def __init__(self):
        self.start_time = None

    def start(self):
        self.start_time = time.perf_counter()

    def get_elapsed_time(self):
        if self.start_time is None:
            return 0
        return time.perf_counter() - self.start_time
    
clock = Timer()
clock.start()

picam1 = Picamera2()
picam2 = Picamera2()
video_config1 = picam1.create_video_configuration()
video_config2 = picam2.create_video_configuration()
picam1.configure(video_config1)
picam2.configure(video_config2)

encoder1 = H264Encoder(10000000)
encoder2 = H264Encoder(10000000)

data = {
    "Lane_No":[], "Start_Time":[], "End_Time":[]
}

ser = serial.Serial("COM12", 9600)
time.sleep(2)


while True:
    recv_data = ser.readline().decode('UTF-8').strip()
    print(recv_data)
    
    if recv_data == "Lane 1 started":
        picam1.start_recording(encoder1, 'test1.h264')
        picam2.start_recording(encoder2, 'test2.h264')
        
    datalist = recv_data.split(" ")
    if datalist[1] not in data["Lane_No"]:
        data["Lane_No"].append(datalist[1])
    if datalist[2] == "started":
        data["Start_Time"].append(clock.get_elapsed_time())
    if datalist[2] == "ended":
        data["End_Time"].append(clock.get_elapsed_time())
    if recv_data == "Lane 2 ended":
        picam1.stop_recording()
        picam2.stop_recording()
        break

os.system("ffmpeg -r 115 -i test1.h264 -c copy test1.mp4")
os.remove('test1.h264')

os.system("ffmpeg -r 115 -i test2.h264 -c copy test2.mp4")
os.remove('test2.h264')

#ffmpeg -i crack_monitoring.h264 crack_monitoring.mp4 : another command to convert it to mp4

data_df = pd.DataFrame(data)
data_df.to_csv("lane.csv")

timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
zip_filename = f"data_{timestamp}.zip"

with zipfile.ZipFile(zip_filename, 'w') as zipf:
    zipf.write("lane.csv")
    zipf.write("test1.mp4")
    zipf.write("test2.mp4")