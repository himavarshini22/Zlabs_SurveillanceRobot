import pandas as pd 
import datetime
import serial 
import time 

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

data = {
    "Lane_No":[], "Start_Time":[], "End_Time":[]
}

ser = serial.Serial("COM12", 9600)
time.sleep(2)


while True:
    recv_data = ser.readline().decode('UTF-8').strip()
    print(recv_data)
    datalist = recv_data.split(" ")
    if datalist[1] not in data["Lane_No"]:
        data["Lane_No"].append(datalist[1])
    if datalist[2] == "started":
        data["Start_Time"].append(clock.get_elapsed_time())
    if datalist[2] == "ended":
        data["End_Time"].append(clock.get_elapsed_time())
    if recv_data == "Lane 2 ended":
        break

data_df = pd.DataFrame(data)
data_df.to_csv("lane.csv")