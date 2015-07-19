/*

 iPhone with 16 Channels Remote Control
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

 Version 1.0 Change Log:
 - Controlling Relay and SSR Modules from iPhone using TouchOSC UI
 - SSR just ON and OFF only
 
 (c)20150719 iLabs for Smart Living with iPhone by Adrian Susianto

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>

byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED}; // Define Arduino MAC Address
byte  ip[] = {192,168,1,101};                 // Define Arduino local IP Address

int OutgoingPort = 8000;  // TouchOSC Outgoing Port
int IncomingPort = 9000;  // TouchOSC Incoming Port
int RelayState   = HIGH;  // Declare Relay to OFF at the beginning (Active LOW State)
int SSRState     = LOW;   // Declare SSR to OFF at the beginning (Active HIGH State)

int Relay1 = 37;  // Set Relay1 at pin 37
int Relay2 = 35;  // Set Relay2 at pin 35
int Relay3 = 33;  // Set Relay3 at pin 33
int Relay4 = 31;  // Set Relay4 at pin 31
int Relay5 = 29;  // Set Relay5 at pin 29
int Relay6 = 27;  // Set Relay6 at pin 27
int Relay7 = 25;  // Set Relay7 at pin 25
int Relay8 = 23;  // Set Relay8 at pin 23

int SSR1 = 22;    // Set SSR1 at pin 22
int SSR2 = 24;    // Set SSR2 at pin 24
int SSR3 = 26;    // Set SSR3 at pin 26
int SSR4 = 28;    // Set SSR4 at pin 28
int SSR5 = 30;    // Set SSR5 at pin 30
int SSR6 = 32;    // Set SSR6 at pin 32
int SSR7 = 34;    // Set SSR7 at pin 34
int SSR8 = 36;    // Set SSR8 at pin 36

EthernetUDP Udp;  // Create UDP message object

void setup()
{
  Ethernet.begin(mac, ip);                               // Define local IP Address
  Udp.begin(OutgoingPort);                               // Start the Ethernet connection

  pinMode(Relay1, OUTPUT); digitalWrite(Relay1, HIGH);   // Set Relay1 Pin Out and reset it
  pinMode(Relay2, OUTPUT); digitalWrite(Relay2, HIGH);   // Set Relay2 Pin Out and reset it
  pinMode(Relay3, OUTPUT); digitalWrite(Relay3, HIGH);   // Set Relay3 Pin Out and reset it
  pinMode(Relay4, OUTPUT); digitalWrite(Relay4, HIGH);   // Set Relay4 Pin Out and reset it
  pinMode(Relay5, OUTPUT); digitalWrite(Relay5, HIGH);   // Set Relay5 Pin Out and reset it
  pinMode(Relay6, OUTPUT); digitalWrite(Relay6, HIGH);   // Set Relay6 Pin Out and reset it
  pinMode(Relay7, OUTPUT); digitalWrite(Relay7, HIGH);   // Set Relay7 Pin Out and reset it
  pinMode(Relay8, OUTPUT); digitalWrite(Relay8, HIGH);   // Set Relay8 Pin Out and reset it

  pinMode(SSR1, OUTPUT); digitalWrite(SSR1, LOW);        // Set SSR1 Pin Out and reset it
  pinMode(SSR2, OUTPUT); digitalWrite(SSR2, LOW);        // Set SSR2 Pin Out and reset it
  pinMode(SSR3, OUTPUT); digitalWrite(SSR3, LOW);        // Set SSR3 Pin Out and reset it
  pinMode(SSR4, OUTPUT); digitalWrite(SSR4, LOW);        // Set SSR4 Pin Out and reset it
  pinMode(SSR5, OUTPUT); digitalWrite(SSR5, LOW);        // Set SSR5 Pin Out and reset it
  pinMode(SSR6, OUTPUT); digitalWrite(SSR6, LOW);        // Set SSR6 Pin Out and reset it
  pinMode(SSR7, OUTPUT); digitalWrite(SSR7, LOW);        // Set SSR7 Pin Out and reset it
  pinMode(SSR8, OUTPUT); digitalWrite(SSR8, LOW);        // Set SSR8 Pin Out and reset it
}


void loop()
{
  OSCReceive();                                         // Running Program and awaiting OSC Data
} 

void OSCReceive()                                       // Receiving OSC Messages
{
  OSCMessage msgIN;                                     // Get Incoming Messages
  int size;                                             // Define Variable to store the OSC data package
  if((size = Udp.parsePacket())>0)                      // Parsing OSC Messages
  {
    while(size--) msgIN.fill(Udp.read());               // Define what control to continue the process
    if(!msgIN.hasError())
    {
      msgIN.route("/lighting/relay1",Relay1Data);       // Is it from Relay1 ?
      msgIN.route("/lighting/relay2",Relay2Data);       // Is it from Relay2 ?
      msgIN.route("/lighting/relay3",Relay3Data);       // Is it from Relay3 ?
      msgIN.route("/lighting/relay4",Relay4Data);       // Is it from Relay4 ?
      msgIN.route("/lighting/relay5",Relay5Data);       // Is it from Relay5 ?
      msgIN.route("/lighting/relay6",Relay6Data);       // Is it from Relay6 ?
      msgIN.route("/lighting/relay7",Relay7Data);       // Is it from Relay7 ?
      msgIN.route("/lighting/relay8",Relay8Data);       // Is it from Relay8 ?  

      msgIN.route("/lighting/ssr1",SSR1Data);           // Is it from SSR1 ?
      msgIN.route("/lighting/ssr2",SSR2Data);           // Is it from SSR2 ?
      msgIN.route("/lighting/ssr3",SSR3Data);           // Is it from SSR3 ?
      msgIN.route("/lighting/ssr4",SSR4Data);           // Is it from SSR4 ?
      msgIN.route("/lighting/ssr5",SSR5Data);           // Is it from SSR5 ?
      msgIN.route("/lighting/ssr6",SSR6Data);           // Is it from SSR6 ?
      msgIN.route("/lighting/ssr7",SSR7Data);           // Is it from SSR7 ?
      msgIN.route("/lighting/ssr8",SSR8Data);           // Is it from SSR8 ?  

      msgIN.route("/lighting/dimmer1",Dimmer1Data);     // Is it from Dimmer1 ?
      msgIN.route("/lighting/dimmer2",Dimmer2Data);     // Is it from Dimmer2 ?
      msgIN.route("/lighting/dimmer3",Dimmer3Data);     // Is it from Dimmer3 ?
      
      msgIN.route("/lighting/reset",Reset);             // Is it Reset Command ?
    }
  }
}

void Relay1Data(OSCMessage &msg, int)                // If from OSC Relay1 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay1, RelayState);                  // Send Relay1 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 1 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 1 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Relay2Data(OSCMessage &msg, int)                // If from OSC Relay2 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay2, RelayState);                  // Send Relay2 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 2 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 2 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Relay3Data(OSCMessage &msg, int)                // If from OSC Relay3 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay3, RelayState);                  // Send Relay3 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 3 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 3 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}


void Relay4Data(OSCMessage &msg, int)                // If from OSC Relay4 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay4, RelayState);                  // Send Relay4 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 4 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 4 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Relay5Data(OSCMessage &msg, int)                // If from OSC Relay5 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay5, RelayState);                  // Send Relay5 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 5 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 5 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Relay6Data(OSCMessage &msg, int)                // If from OSC Relay6 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay6, RelayState);                  // Send Relay6 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 6 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 6 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Relay7Data(OSCMessage &msg, int)                // If from OSC Relay7 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay7, RelayState);                  // Send Relay7 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 7 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 7 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Relay8Data(OSCMessage &msg, int)                // If from OSC Relay8 Command then
{
  RelayState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(Relay8, RelayState);                  // Send Relay8 command from TouchOSC 
  RelayState = !RelayState;                          // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (RelayState) msgOUT.add("RELAY 8 Activated");   // Set Character Message to display
  else msgOUT.add("RELAY 8 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR1Data(OSCMessage &msg, int)                  // If from OSC SSR1 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR1, SSRState);                      // Send SSR1 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 1 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 1 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR2Data(OSCMessage &msg, int)                  // If from OSC SSR2 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR2, SSRState);                      // Send SSR1 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 2 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 2 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR3Data(OSCMessage &msg, int)                  // If from OSC SSR3 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR3, SSRState);                      // Send SSR3 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 3 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 3 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR4Data(OSCMessage &msg, int)                  // If from OSC SSR4 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR4, SSRState);                      // Send SSR4 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 4 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 4 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR5Data(OSCMessage &msg, int)                  // If from OSC SSR5 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR5, SSRState);                      // Send SSR5 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 5 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 5 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR6Data(OSCMessage &msg, int)                  // If from OSC SSR6 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR6, SSRState);                      // Send SSR6 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 6 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 6 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR7Data(OSCMessage &msg, int)                  // If from OSC SSR7 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR7, SSRState);                      // Send SS71 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 7 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 7 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void SSR8Data(OSCMessage &msg, int)                  // If from OSC SSR8 Command then
{
  SSRState = (boolean) msg.getFloat(0);              // Get Data and store as Boolean Mode
  digitalWrite(SSR8, SSRState);                      // Send SSR8 command from TouchOSC 
  OSCMessage msgOUT("/lighting/display");            // Define TouchOSC Control for Display
  if (SSRState) msgOUT.add("SSR 8 Activated");       // Set Character Message to display
  else msgOUT.add("SSR 8 Deactivated");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Dimmer1Data(OSCMessage &msg, int)               // If from Dimmer1 then
{
  int dimmer1 = msg.getFloat(0);                     // Store Incoming Message to variable
  OSCMessage msgOUT("/lighting/dimmer1data");        // Define which TouchOSC Control to send with Message
  msgOUT.add(dimmer1);                               // Define Message from Variable dimer1
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Dimmer2Data(OSCMessage &msg, int)               // If from Dimmer2 then
{
  int dimmer2 = msg.getFloat(0);                     // Store Incoming Message to variable
  OSCMessage msgOUT("/lighting/dimmer2data");        // Define which TouchOSC Control to send with Message
  msgOUT.add(dimmer2);                               // Define Message from Variable dimer1
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}

void Dimmer3Data(OSCMessage &msg, int)               // If from Dimmer3 then
{
  int dimmer3 = msg.getFloat(0);                     // Store Incoming Message to variable
  OSCMessage msgOUT("/lighting/dimmer3data");        // Define which TouchOSC Control to send with Message
  msgOUT.add(dimmer3);                               // Define Message from Variable dimer1
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);     // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                  // Send OSC message to TouchOSC
  Udp.endPacket();                                   // Send End Message signature
  msgOUT.empty();                                    // Set Free space occupied by message
}


void Reset(OSCMessage &msg, int)                  // Reset Procedure
{
  ResetLedON();                                   // Turn Reset Indicator ON
  DisplayResetting();                             // Display Resetting to indicate Reset Sequence Initiated
  ResetTouchOSCL1();                              // Reset Switch1 Relay and State
  ResetTouchOSCL2();                              // Reset Switch2 Relay and State
  ResetTouchOSCL3();                              // Reset Switch3 Relay and State
  ResetTouchOSCL4();                              // Reset Switch4 Relay and State
  ResetTouchOSCL5();                              // Reset Switch5 Relay and State
  ResetTouchOSCL6();                              // Reset Switch6 Relay and State
  ResetTouchOSCL7();                              // Reset Switch7 Relay and State
  ResetTouchOSCL8();                              // Reset Switch8 Relay and State

  ResetTouchOSCSSR1();
  ResetTouchOSCSSR2();
  ResetTouchOSCSSR3();
  ResetTouchOSCSSR4();
  ResetTouchOSCSSR5();
  ResetTouchOSCSSR6();
  ResetTouchOSCSSR7();
  ResetTouchOSCSSR8();
  
  ResetDimmer1();                                 // Send fader1 back to initial state at 0
  ResetDimmer1DataDisplay();                      // Reset Dimmer1 Data Display to 0
  ResetDimmer2();                                 // Send fader2 back to initial state at 0
  ResetDimmer2DataDisplay();                      // Reset Dimmer2 Data Display to 0
  ResetDimmer3();                                 // Send fader3 back to initial state at 0
  ResetDimmer3DataDisplay();                      // Reset Dimmer3 Data Display to 0

  delay(200);                                     // Hold a moment
  ResetLedOFF();                                  // Turn Reset Indicator OFF
  DisplayStatusOK();                              // Display all done and System OK
}

void ResetTouchOSCL1()                            // Resetting Light1 Control
{
  digitalWrite(Relay1, HIGH);                  // Turn OFF Switch1 Relay
  OSCMessage msgOUT("/lighting/relay1");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL2()                            // Resetting Light2 Control
{
  digitalWrite(Relay2, HIGH);                  // Turn OFF Switch2 Relay
  OSCMessage msgOUT("/lighting/relay2");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL3()                            // Resetting Light3 Control
{
  digitalWrite(Relay3, HIGH);                  // Turn OFF Switch3 Relay
  OSCMessage msgOUT("/lighting/relay3");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL4()                            // Resetting Light4 Control
{
  digitalWrite(Relay4, HIGH);                  // Turn OFF Switch4 Relay
  OSCMessage msgOUT("/lighting/relay4");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL5()                            // Resetting Light5 Control
{
  digitalWrite(Relay5, HIGH);                  // Turn OFF Switch5 Relay
  OSCMessage msgOUT("/lighting/relay5");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL6()                            // Resetting Light6 Control
{
  digitalWrite(Relay6, HIGH);                  // Turn OFF Switch6 Relay
  OSCMessage msgOUT("/lighting/relay6");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL7()                            // Resetting Light7 Control
{
  digitalWrite(Relay7, HIGH);                  // Turn OFF Switch7 Relay
  OSCMessage msgOUT("/lighting/relay7");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL8()                            // Resetting Light8 Control
{
  digitalWrite(Relay8, HIGH);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/relay8");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR1()                            // Resetting Light8 Control
{
  digitalWrite(SSR1, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr1");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR2()                            // Resetting Light8 Control
{
  digitalWrite(SSR2, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr2");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR3()                            // Resetting Light8 Control
{
  digitalWrite(SSR3, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr3");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR4()                            // Resetting Light8 Control
{
  digitalWrite(SSR4, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr4");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR5()                            // Resetting Light8 Control
{
  digitalWrite(SSR5, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr5");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR6()                            // Resetting Light8 Control
{
  digitalWrite(SSR6, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr6");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR7()                            // Resetting Light8 Control
{
  digitalWrite(SSR7, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr7");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCSSR8()                            // Resetting Light8 Control
{
  digitalWrite(SSR8, LOW);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/ssr8");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}



void ResetDimmer1()                               // Resetting Dimmer1 Control
{
  OSCMessage msgOUT("/lighting/dimmer1");         // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetDimmer1DataDisplay()                    // Resetting Dimmer1 Data Display to 0
{
  OSCMessage msgOUT("/lighting/dimmer1data");     // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetDimmer2()                               // Resetting Dimmer2 Control
{
  OSCMessage msgOUT("/lighting/dimmer2");         // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetDimmer2DataDisplay()                    // Resetting Dimmer2 Data Display to 0
{
  OSCMessage msgOUT("/lighting/dimmer2data");     // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetDimmer3()                               // Resetting Dimmer3 Control
{
  OSCMessage msgOUT("/lighting/dimmer3");         // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetDimmer3DataDisplay()                    // Resetting Dimmer3 Data Display to 0
{
  OSCMessage msgOUT("/lighting/dimmer3data");     // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void DisplayStatusOK()                            // Display System OK Message Procedure
{
  OSCMessage msgOUT("/lighting/display");         // Define TouchOSC Control for Display
  msgOUT.add("Status : OK");                      // Set Character Message to display
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void DisplayResetting()                           // Display Resetting Message Procedure
{
  OSCMessage msgOUT("/lighting/display");         // Define TouchOSC Control for Display
  msgOUT.add("Resetting ...");                    // Set Character Message to display
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetLedON()                                 // Turn ON Reset LED Procedure
{
  OSCMessage msgOUT("/lighting/led1");            // Define TouchOSC LED to be ON State
  msgOUT.add(1);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message}
}

void ResetLedOFF()                                // Turn OFF Reset LED Procedure
{
  OSCMessage msgOUT("/lighting/led1");            // Define TouchOSC LED to be OFF State
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message}
}
