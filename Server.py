#This program will allow a user to connect to local host and then spit all data out
#from the logged OBD2 port to simulate actual communication between the OBD2 and the
#raspberry pi, so i dont need to be in a car
# Andrew Brashich
import socket
from time import sleep

#Variables for local host
_init_s = True
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
    _temp = ''
    _list_iter = 0
    _search = True
    with open("Init.txt","r+", newline='') as _Init_file:
        for _line in _Init_file:
            if _search == True:
                for i, _Init_AT in enumerate(_Start_AT):
                    if _Init_AT == _line:
                        _list_iter = i
                        _search = False
                        break
                return('ERROR')
            else:
                _temp = _temp + _line.rstrip('\n')
                if _line == '>\n':
                    _search = True
                if _line.endswith('\n'):
                    _Start_AT[_list_iter].append(_temp)
                    _temp = ''

    _list_iter = 0
    _search = True
    _temp = ''
    with open("logging1.txt","r+", newline='') as _Logging:
        for _line in _Logging:
            if _search == True:
                for i, _Ids in enumerate(_Pids):
                    if _Ids == _line:
                        _list_iter = i
                        _search = False
                        break
                    else:
                        return('ERROR')
            else:
                _temp = _temp + _line.rstrip('\n')
                if _line == '>\n':
                    _search = True
                if _line.endswith('\n'):
                    _Pids[_list_iter].append(_temp)
                    _temp = ''
    return None
def _Search_init(_recv):
    _list = []
    for i, _Init_AT in enumerate(_Start_AT):
        if _Init_AT == _recv:
            if len(_Start_AT[i]) > 1:
                    for value in _Start_AT[i][1:]:
                        _list.append(value)
                        del _Pids[i][1]
                        if value.endswith('>'):
                            return _list
        else:
            return False, None

def _Search_Pids(_recv):
    _list = []
    for i, _Init_AT in enumerate(_Pids):
        if _Init_AT == _recv and len(_Pids[i]) > 1:
            if len(_Pids[i]) > 1:
                for value in _Pids[i][1:]:
                    _list.append(value)
                    del _Pids[i][1]
                    if value.endswith('>'):
                        return _list

    return ['NODATA\r','>\r']



#Opens the save logging data for use
def main():
    if not _Init_files() == error:
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
                while True:
                    data = conn.recv(64)
                    if data.endswith(b'\r'):
                        if _init_s == True:
                            bool, _list = _Search_init(data)
                            if bool == True:
                                for i in _list:
                                    conn.sendall(i)
                            else:
                                _init_s = bool
                        else:
                            _list = _Search_Pids(data)
                            for str in _list:
                                conn.sendall(str)
                    else:
                        conn.sendall(b'?\r')
                        conn.sendall(b'>\r')
