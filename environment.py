import serial
import requests

roomID = 'CS-225'
arduino = serial.Serial('COM4', 9600, timeout=12)

def getSound():
    arduino.write(bytes('1', 'utf-8'))
    response = arduino.read()
    val = int.from_bytes(response, 'big')
    if(val == 0):
        return "LOW"
    if(val == 1):
        return "MEDIUM"
    if(val == 2):
        return "HIGH"
    

def getTemp():
    arduino.write(bytes('2', 'utf-8'))
    response = arduino.read()
    val = int.from_bytes(response, 'big')
    if(val == 0):
        return "LOW"
    if(val == 1):
        return "MEDIUM"
    if(val == '2'):
        return "HIGH"

def updateSettings():
    temp = getTemp()
    sound = getSound
    sURL = "http://sds.samchatfield.com/api/room/%s" % roomID
    data = { "temperatureLevel" : temp, "noiseLevel" : sound }
    request = requests.put(sURL, json=data )
    request.raise_for_status()