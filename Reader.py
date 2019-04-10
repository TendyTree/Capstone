#This program will be used to grab incoming data from port 3500
# on ip 192.168.0.10 from the OBD2 reader for analysis.
#This project is being based off the ELM327 architecture.
# Andrew Brashich
import socket

#Set up Variables for the connection
LOGSOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
OBD2_IP = "127.0.0.1"
OBD2_PORT = 35000


def send_recv(_Send_command):
    _data = ''
    _decode_data = _Send_command + '\r'
    _Send_command += '\r'
    LOGSOCKET.sendall(_Send_command.encode('utf8'))
    while True:
        _data = LOGSOCKET.recv(64)
        if _data.endswith(b'\r') or len(_data) > 128 or _data.endswith(b'>'):
            _decode_data = _decode_data + _data.decode('utf8') + "\n"
            if _data.endswith(b'>'):
                break
    return _decode_data #contains _Send_command + \r + _data + \n + _data + \n...

def _InitOBD():
    with open("Init9.txt","w+", newline='') as _Init_file:
        _Init_commands = ("ATZ","ATD0","ATSP0","ATE0","ATH1","ATST64","ATS0","ATAT1","0100")
        for _commands in _Init_commands:
            _recv_data = send_recv(_commands)
            _Init_file.write(_recv_data)
            if 'NODATA' in _recv_data or 'CAM ERROR' in _recv_data:
                return False
        print("Done with INIT")
    return True



def _get_data():
    _data = ''
    with open("logging9.txt","w+", newline='') as _Logging:
        _Pids = ('0105','010C','010D','0144','0146','0149','ATRV')
        #Coolant,rpm,Speed,MAF,Fuel air Command,Ambent air,Pedal Position,Volatge

        while True:
            for pids in _Pids:
                _recv_data = send_recv(pids)
                _Logging.write(_recv_data)
                if 'CAN ERROR' in _recv_data:
                    return None


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
