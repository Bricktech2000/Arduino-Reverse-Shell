Digispark Reverse Shell
=======================

A simple reverse shell script using a digispark

Overview
--------

Below is a basic overview of the functionnality of this project:

* A pre-programmed Digispark board is plugged into a computer, which runs commands by emulating a USB keyboard
* Netcat gets downloaded and executed on the target computer, which then tries to connect to a predefined server
* The server listens for Netcat connections and when one is found, a tunnel is created to allow the host to send commands to the victim computer

Requirements
------------

* Python 3
* Netcat installed under `Digispark Reverse Shell/nc.exe`
* Arduino IDE with Digispark boards installed
* A Digispark board

Port Setup
----------

If you wish to do so, you can edit the ports used for communication between the victim and the server. The default ones are `54414` for the HTTP download and `47017` for the Netcat listener. If you wish to edit them, make sure to change them in both `Digispark Reverse Shell\server.py` and `Digispark Reverse Shell\Reverse_Shell_Digispark\Reverse_Shell_Digispark.ino` for the client-server synchronization to work.

Host Setup
----------

Before using this program, you must edit the server host in `Digispark Reverse Shell\Reverse_Shell_Digispark\Reverse_Shell_Digispark.ino`. The default value is `localhost`, but you need to replace it with a static server ip or a domain name pointing to your server. This will make sure that the Digispark will connect to the right host when performing the reverse shell attack.

Digispark Setup
---------------

1. Download and extract the [Digispark drivers](https://github.com/digistump/DigistumpArduino/releases)
2. Run `DPinst64.exe` to install the drivers
3. Download the [updated Digispark bootloader](https://drive.google.com/file/d/1z55WoeLUVXS764OyOiC_GKl_kp9dt2BI/view), which removes the 5-second upload delay
4. Drag `main.hex` on top of `micronucleus.exe` in the driver folder downloaded previously
5. Plug in the Digispark board and make sure the new bootloader is successfully installed

Uploading to the Digispark
--------------------------

1. Open up `Digispark Reverse Shell\Reverse_Shell_Digispark\Reverse_Shell_Digispark.ino` in the Arduino IDE
2. Select `Digispark (Default - 16.5mhz)` under `Boards` (if you do not see this board, make sure you follow [these instructions](https://digistump.com/wiki/digispark/tutorials/connecting))
3. On the Digispark, connect pins `P0` and `GND` together using a jumper wire in order to enter programming mode
4. Upload the sketch from the Arduino IDE
5. When asked, plug in the Digispark Board and make sure the code gets uploaded successfully
6. Remove the jumper connecting pins `P0` and `GND` to exit programming mode

The Digispark board is now ready. It can be plugged into any computer and it will execute its preprogrammed script, which downloads Netcat and tries to connect on the specified host and port.

If you wish to do so, a small script called `Reverser.py` can be used to add more keyboard layouts to the Digispark program.

Server Setup
------------

To boot up the server, run the `server.py` script. To start the Netcat listener, run a second instance of the `server.py` script, which should automatically detect that the first instance is already running. This is the interface that will allow the host to run any Powershell command remotely.
