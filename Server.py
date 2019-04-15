#This program will allow a user to connect to local host and then spit all data out
#from the logged OBD2 port to simulate actual communication between the OBD2 and the
#raspberry pi, so i dont need to be in a car
# Andrew Brashich
import socket
from time import sleep

#Variables for local host
_init_s = True
HOST_IP = "127.0.0.1"
HOST_PORT = 35000

_Pids = [
['0105\r'],#Coolant
['010C\r'],#rpm
['010D\r'],#Speed
['0110\r'],#MAF
['0144\r'],#Fuel air Command
['0146\r'],#Ambent air
['0149\r'],#Pedal Position
['ATRV\r']#Volatge
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
    with open("Init2.txt","r+", newline='') as _Init_file:
        for _line in _Init_file:
            if _search == True:
                for i, _Init_AT in enumerate(_Start_AT):
                    if _Init_AT[0] == _line:
                        _list_iter = i
                        _search = False
                        break
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
    with open("logging2.txt","r+", newline='') as _Logging:
        for _line in _Logging:
            if _search == True:
                for i, _Ids in enumerate(_Pids):
                    if _Ids[0] == _line:
                        _list_iter = i
                        _search = False
                        break
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
        if _Init_AT[0] == _recv.decode('utf8'):
            if len(_Start_AT[i]) > 1:
                    for value in _Start_AT[i][1:]:
                        _list.append(value)
                        del _Start_AT[i][1]
                        if value.endswith('>'):
                            return True,_list
    return False, None

def _Search_Pids(_recv):
    _list = []
    for i, _Init_AT in enumerate(_Pids):
        if _Init_AT[0] == _recv.decode('utf8'):
            if len(_Pids[i]) > 1:
                for value in _Pids[i][1:]:
                    _list.append(value)
                    del _Pids[i][1]
                    if value.endswith('>'):
                        return _list

    return ['NO DATA\r','>\r']




def main():
    _init_s = True
    if not _Init_files() == 'error':
        for i in _Start_AT:
            print(i)
        for a in _Pids:
            print(a)
    #Initialize the socket for the server and set it to listening
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as LOGSERVER:
            LOGSERVER.bind((HOST_IP, HOST_PORT))
            LOGSERVER.listen(1)
            print("listening")
            conn, addr = LOGSERVER.accept()

            with conn:
                print('Connected by', addr)
                while True:
                    data = conn.recv(64)
                    print(data)
                    sleep(.3)
                    if not data:
                        break
                    if data.endswith(b'\r'):
                        if _init_s == True:
                            bool, _list = _Search_init(data)
                            if bool == True:
                                for i in _list:
                                    conn.sendall(i.encode('utf8'))
                            else:
                                _init_s = bool
                        if _init_s == False:
                            _list = _Search_Pids(data)
                            for str in _list:
                                print(str.encode('utf8'))
                                conn.sendall(str.encode('utf8'))
                    else:
                        if(data == b''):
                            break
                        print(data)
                        conn.sendall(b'?\r')
                        conn.sendall(b'>\r')
    print("end");
    input()

if __name__ == '__main__':
    main()
