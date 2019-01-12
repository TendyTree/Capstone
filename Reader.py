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
    _decode_data=''
    _Send_command += '\r'
    LOGSOCKET.sendall(_Send_command)
    print()
        while True:
            data = LOGSOCKET.recv(128)
            print(data)
            if not data


    return _decode_data

def _InitOBD():
    with open("Init.txt","w+") as _Init_file
        _Init_commands = ("ATZ","ATD0","ATSP0","ATE0","ATH1","ATST64","ATS0","ATAT1","0100")
        for _commands in _Init_commands:
            _Init_file.write(_commands + '\n' + send_recv(_commands) + '\n')
        print("Done with INIT")
    return True



def _get_data():
    _data = ''
    with open("logging1.txt","w+") as _Logging
        _Pids = ('010C','010D','0105','019A','0145','0146','015C','015E','01A4','01A6','ATRV')
        while True
            for pids in _Pids:
                _data = send_recv(pids)
                _Logging.write(pids + '\n' + _data + '\n')
                if _data == 'CAMERROR' or _data = 'NODATA'
                    break



    while True:
        data = LOGSOCKET.recv(32)
        if not data:
            break
        print(data)
        LOGGING.write(data.decode('utf-8'))




def main():
    #sets the timeout for the connection to the OBD2 reader to 10 seconds.
    #If not connected in amount of time it will throw an error to you
    LOGSOCKET.settimeout(10)
    try:
        LOGSOCKET.connect((OBD2_IP, OBD2_PORT))
    except socket.timeout:
            print("Could not connect to the OBD2, please make sure it is plugged in.")
    except socket.error:
            print("Error trying to connect")
    LOGSOCKET.settimeout(None)
    if _InitOBD == True:
        _get_data()

    #Closes the program
    LOGSOCKET.close()
    print("Closed")
    input()


if __name__ == '__main__':
    main()
