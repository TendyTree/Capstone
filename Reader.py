#This program will be used to grab incoming data from port 3500
# on ip 192.168.0.10 from the OBD2 reader for analysisself.
# Andrew Brashich
import socket

LOGSOCKET = socket.socket()
LOGGING = open("logging.txt","w+")
OBD2_IP = "192.168.0.10"
OBD2_PORT = 3500

LOGSOCKET.connect((OBD2_IP, OBD2_PORT))
while True:
    data = LOGSOCKET.recv(32)
    if not data:
        break
    print(data)
    LOGGING.write(data)

LOGGING.close()
