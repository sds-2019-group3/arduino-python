import serial
import datetime
import requests

room = 225

def getFree():
    currentDT = datetime.datetime.now()
    currentDTf = currentDT.strftime("%Y-%m-%d")
    dt_string = ("%sT%d:00Z" % (currentDTf, currentDT.hour))
    testURL = "http://sds.samchatfield.com/api/room/CS-225/bookings/2019-03-27T19:00Z"
    url = ("http://sds.samchatfield.com/api/room/CS-%i/bookings/%s" % (room, dt_string))
    res = requests.get(url)
    if (res.status_code == 500):
        print("No Booking")
        return True
    else:
        print("Booking")
        return False

arduino = serial.Serial('COM4', 9600, timeout=None)
while True:
    data = arduino.readline()[0]
    print(data)
    if (data == 49):
        print("Checking Availability")
        if getFree():
            print("Room Free")
            arduino.write(bytes('1', 'utf-8'))
        else:
            print("Room Booked")
            arduino.write(bytes('0', 'utf-8'))