#This program will be used to grab incoming data from port 3500
# on ip 192.168.0.10 from the OBD2 reader for analysisself.
# Andrew Brashich
import socket
x = True
LOGSOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
LOGGING = open("logging.txt","w+")
OBD2_IP = "192.168.0.10"
OBD2_PORT = 3500
LOGSOCKET.settimeout(10)
print("loop")

try:
    LOGSOCKET.connect((OBD2_IP, OBD2_PORT))
except socket.timeout:
    x = False
    print("Could not connect to the OBD2, please make sure it is plugged in.")
except socket.error:
    x = False
    print("Error trying to connect")

LOGSOCKET.settimeout(None)
print("Printing data)
while (x):
    data = LOGSOCKET.recv(32)
    if not data:
        break
    print(data)
    LOGGING.write(data.decode('utf-8'))

LOGGING.close()
print("Closed")
