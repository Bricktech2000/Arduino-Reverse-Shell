# Arduino Reverse Shell

_A simple reverse shell script using an Arduino Leonardo_

## Overview

Below is a basic overview of the functionnality of this project:

- A pre-programmed Arduino Leonardo board is plugged into a computer, which runs commands by emulating a USB keyboard
- Netcat gets downloaded and executed on the target computer, which then tries to connect to a predefined server
- The server listens for Netcat connections and when one is found, a tunnel is created to allow the host to send commands to the victim computer

## Requirements

- Python 3
- Netcat installed under `Arduino Reverse Shell\server\nc.exe`
- Arduino IDE
- An ATMEGA32U4-based arduino board (such as the Arduino Leonardo or the Arduino Beetle ATMEGA32U4)

## Port Setup

If you wish to do so, you can edit the ports used for communication between the victim and the server. The default ones are `54414` for the HTTP download and `47017` for the Netcat listener. If you wish to edit them, make sure to change them in both `Arduino Reverse Shell\server\server.py` and `Arduino Reverse Shell\arduino_sketch\arduino_sketch.ino` for the client-server synchronization to work.

## Host Setup

Before using this program, you must edit the server host in `Arduino Reverse Shell\arduino_sketch\arduino_sketch.ino`. The default value is `localhost`, but you need to replace it with a static server ip or a domain name pointing to your server. This will make sure that the Arduino Leonardo will connect to the right host when performing the reverse shell attack.

## Uploading to the Arduino

1. Open up `Arduino Reverse Shell\arduino_sketch\arduino_sketch.ino` in the Arduino IDE
2. Select `Arduino Leonardo` under `Boards`
3. Upload the sketch from the Arduino IDE
4. Plug in the Arduino Leonardo Board and make sure the code gets uploaded successfully

The Arduino Leonardo board is now ready. It can be plugged into any computer and it will execute its preprogrammed script, which downloads Netcat and tries to connect on the specified host and port.

If you wish to do so, a small script called `Reverser.py` can be used to add more keyboard layouts to the Arduino Leonardo program.

## Server Setup

To boot up the server, run the `server.py` script under `Arduino Reverse Shell\server\server.py`. To start the Netcat listener, run a second instance of the `server.py` script, which should automatically detect that the first instance is already running. This is the interface that will allow the host to run any Powershell command remotely.
