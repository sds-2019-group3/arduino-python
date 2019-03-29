import requests
import time
import os
import serial

roomID = "CS-225"

arduino = serial.Serial('COM4', 9600, timeout=0.1)

def downspeed():
    url = "http://ipv4.download.thinkbroadband.com/20MB.zip"

    startTime = time.time()
    file = requests.get(url)
    endTime = time.time()

    timeTaken = endTime - startTime
    fileSize = int(file.headers['Content-Length'])/1048576

    return (fileSize / timeTaken)

def getTemp():
    return

def getNoise():
    return

sURL = "http://sds.samchatfield.com/api/room/%s" % roomID
data = { "wifiSpeed" : downspeed()*8 }
request = requests.put(sURL, json=data )
request.raise_for_status()