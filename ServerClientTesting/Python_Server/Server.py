#Andrew Brashich
#A Quick python server for testing with qt sockets.
#Will allow qt to connect and anything that is sent from the 
#qt client will be sent back to Qt with additional message "Recieved: ..."
#as well as printing the raw data on the python side

import socket

Host_IP = "127.0.0.1"
Host_Port = 35000

def main():
    print('Hello and welcome to the server!')
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as LOGSERVER:
        LOGSERVER.bind((Host_IP, Host_Port))
        LOGSERVER.listen(1)
        print("listening")
        conn, addr = LOGSERVER.accept()
        with conn:
            print('Connected by', addr)
            while True:
                data = conn.recv(64)
                print(data)
                if not data:
                    break
                conn.sendall(("Server sent:" + data.decode('utf-8')).encode('utf-8'))
                print("sent")
    print('Now leaving')

if __name__ == '__main__':
    main()                    
					
