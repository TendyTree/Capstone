#This program will allow a user to connect to local host and then spit all data out
#from the logged OBD2 port to simulate actual communication between the OBD2 and the
#raspberry pi, so i dont need to be in a car
# Andrew Brashich
import socket
from time import sleep

#Variables for local host
HOST_IP = "127.0.0.1"
HOST_PORT = 3500
_Pids = [
['010C\r'],
['010D\r'],
['0105\r'],
['019A\r'],
['0145\r'],
['0146\r'],
['015C\r'],
['015E\r'],
['01A4\r'],
['01A6\r'],
['ATRV\r']
]
_Start_AT = [
['ATZ\r'],
['ATD0\r'],
['ATSP0\r'],
['ATE0\r'],
['ATH1\r'],
['ATST64\r'],
['ATS0\r'],
['ATAT1\r'],
['0100\r']
]

def _Init_files():
    _list_iter = 0
    _list_bool = False
    with open("Init.txt","w+") as _Init_file:
        for _line in _Init_file:
            _line = _line.rstrip() + '\r'
            for i, _Init_AT in enumerate(_Start_AT):
                if _Init_AT == _line:
                    _list_iter = i
                    _list_bool = true
                    break
            if  not _list_bool:
                _Start_AT[_list_iter].append(_line)
            else:
                _list_bool = false
    _list_iter = 0
    _list_bool = False
    with open("logging1.txt","w+") as _Logging:
        for _line in _Logging:
            _line = _line.rstrip() + '\r'
            for i, _Init_PIDS in enumerate(_Pids):
                if _Init_PIDS == _line:
                    _list_iter = i
                    _list_bool = true
                    break
            if  not _list_bool:
                _Pids[_list_iter].append(_line)
            else:
                _list_bool = false

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

		#recieves DATA and then parse what needed
		#switch case then sends out the data


        with conn:
            print('Connected by', addr)
            for line in LOGGING:
                conn.sendall(str.encode(line))
                sleep(0.05)
