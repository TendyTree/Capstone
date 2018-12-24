#This program will be used to grab incoming data from port 3500
# on ip 192.168.0.10 from the OBD2 reader for analysisself.
# Andrew Brashich
import socket

#Set up Variables for the connection
LOGSOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
LOGGING = open("logging.txt","w+")
OBD2_IP = "192.168.0.10"
OBD2_PORT = 3500

#sets the timeout for the connection to the OBD2 reader to 10 seconds.
#If not connected in amount of time it will throw an error to you
LOGSOCKET.settimeout(10)
try:
    LOGSOCKET.connect((OBD2_IP, OBD2_PORT))
    
    #Waits to recieve the data from the OBD2 reader and then stores it
    #in the logging file.
    while True:
        data = LOGSOCKET.recv(32)
        if not data:
            break
        print(data)
        LOGGING.write(data.decode('utf-8'))
except socket.timeout:
    x = False
    print("Could not connect to the OBD2, please make sure it is plugged in.")
except socket.error:
    x = False
    print("Error trying to connect")

#Closes the program
LOGSOCKET.close()
LOGGING.close()
print("Closed")
