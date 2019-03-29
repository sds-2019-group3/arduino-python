import serial

def getBookingUsed():
    arduino = serial.Serial('COM4', 9600, timeout=0.1)
    arduino.write(bytes('1', 'utf-8'))
    while (arduino.inWaiting() == 0): 
        pass
    response = arduino.readline()[0]
    if (response == '1'):
        return True
    else:
        return False

while True:
    print(getBookingUsed())