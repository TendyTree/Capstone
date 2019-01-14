#This program will be used to grab incoming data from port 3500
# on ip 192.168.0.10 from the OBD2 reader for analysis.
#This project is being based off the ELM327 architecture.
# Andrew Brashich
import socket

#Set up Variables for the connection
LOGSOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
OBD2_IP = "192.168.0.10"
OBD2_PORT = 3500


def send_recv(_Send_command):
    _data = ''
    _decode_data = _Send_command + '\r'
    _Send_command += '\r'
    LOGSOCKET.sendall(_Send_command)
    while True:
        _data = LOGSOCKET.recv(64)
        print(data)
        if _data.endswith(b'\r') or _data>128 or _data.endswith('>'):
            _decode_data = _decode_data + a.decode('utf8') + "\n"
            if _data.endswith('>'):
                break
    print(_decode_data)
    return _decode_data #contains _Send_command + \r + _data + \n + _data + \n...

def _InitOBD():
    with open("Init.txt","w+", newline='') as _Init_file:
        _Init_commands = ("ATZ","ATD0","ATSP0","ATE0","ATH1","ATST64","ATS0","ATAT1","0100")
        for _commands in _Init_commands:
            _recv_data = send_recv(_commands)
            _Init_file.write(_recv_data)
            if 'NODATA' in _recv_data or 'CAMERROR' in _recv_data:
                return False
        print("Done with INIT")
    return True



def _get_data():
    _data = ''
    with open("logging1.txt","w+", newline='') as _Logging:
        _Pids = ('010C','010D','0105','019A','0145','0146','015C','015E','01A4','01A6','ATRV')
        while True:
            for pids in _Pids:
                _recv_data = send_recv(pids)
                _Logging.write(_recv_data)
                if 'NODATA' in _recv_data or 'CAMERROR' in _recv_data:
                    return


def main():
    #sets the timeout for the connection to the OBD2 reader to 10 seconds.
    #If not connected in amount of time it will throw an error to you
    LOGSOCKET.settimeout(10)
    print('try')
    try:
        LOGSOCKET.connect((OBD2_IP, OBD2_PORT))
        LOGSOCKET.settimeout(None)
        print('hi')
        if _InitOBD() == True:
                _get_data()
    except socket.timeout:
            print("Could not connect to the OBD2, please make sure it is plugged in.")
    except socket.error:
            print("Error trying to connect")


    #Closes the program
    LOGSOCKET.close()
    print("Closed")
    input()


if __name__ == '__main__':
    main()
