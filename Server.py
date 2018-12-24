#This program will allow a user to connect to local host and then spit all data out
#from the logged OBD2 port to simulate actual communication between the OBD2 and the
#raspberry pi, so i dont need to be in a car
# Andrew Brashich
import socket
from time import sleep

#Variables for local host
HOST_IP = "127.0.0.1"
HOST_PORT = 3500

#Opens the save logging data for use
with open('logging.txt','r') as LOGGING:

    #Initialize the socket for the server and set it to listening
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as LOGSERVER:
        LOGSERVER.bind((HOST_IP, HOST_PORT))
        LOGSERVER.listen(1)
        print("listening")
        conn, addr = LOGSERVER.accept()

        #With the connection, send all data from file with a 5 milisecond delayself.
        #After it closes the connection
        with conn:
            print('Connected by', addr)
            for line in LOGGING:
                conn.sendall(str.encode(line))
                sleep(0.05)
