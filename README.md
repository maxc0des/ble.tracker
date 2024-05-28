# BLE Tracker
⚠️Might not work with IOS devices⚠️
## About
"BLE Tracker" is a like buget AirTag. It constantly searches for the given MAC adress (for examlpe the mac of your phone). If it cant find the adress anymore, it assumes that you left the Tracker and triggers an alarm,so you dont loose the Tracker. The Tracker, can also display contact inforamtion if you've lost it.
## Components
-Esp32<br>
-Active Buzzer<br>
-Button
## Setup
1.You will need an app like "beacon scope", so your device constatly sends out a ble signal. Might not work with IOS devices!<br>
2. Enter your devices Bluetooth MAC Adress in line 13.<br>
3. You might want to change the text displayed when the tracker is lost in line 74+75.<br>
3. You showld be ready to go!<br>
This project is based on this video so if you have problems with setting up the ble part you should watch it https://www.youtube.com/watch?v=YN42n9dQSv8
## Wiring
Button-> RST, GND | Buzzer-> change pin in line 13, GND 
## Contact
If you have any questions or ideas about the project send me a message on discord(@maxcantsk8) or instagram(@maxx.8784)
