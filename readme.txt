iPhone 16 Channels Remote Control
Version: 1.0

Description:
Build iPhone to Remotely Control Home Lighting and Switches.
Lighting and Switches are controlled by 8CH Relays and 8CH Solid State Relays.
These Relays and SSR are connected to Arduino Mega 2560 and controlled via Ethernet.
OSC protocol is used to communicate between iPhone User Interface Remote Control to Arduino
By translating this OSC message, Arduino then directly command SSR and Relay modules

Hardware Configuration:
Ethernet Shield : A0 ,A1 ,D2 ,D10,D11,D12,D13
8 Channel SSR   : D22,D24,D26,D28,D30,D32,D34,D36
8 Channel Relay : D23,D25,D27,D29,D31,D33,D35,D37

Library:
Ethernet : Arduino IDE
OSCuino  : https://github.com/CNMAT/OSC
 
(c)20150719 iLabs for Smart Living with iPhone by Adrian Susianto
