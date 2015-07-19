/*

 Receiving OSC Data from TouchOSC
 Version: 1.0
 
 Function:
 Receiving OSC Data to Control AC 220V lighting
 
 Description:
 Create Control Panel using TouchOSC Editor and assign Arduino to handle OSC Data coming from Ethernet to control Switch System
  
 Hardware Configuration:
 Ethernet Shield: D10,D11,D12,D13,D50,D51,D52,D53
 Pin 2 [DIG]  : Output AC Switch 1
 Pin 3 [DIG]  : Output AC Switch 2
 Pin 4 [DIG]  : Output AC Switch 3
 Pin 5 [DIG]  : Output AC Switch 4

 Help and Contributors:
 Trippy Switch : http://trippylighting.com/teensy-arduino-ect/touchosc-and-arduino-oscuino/
 OSCuino Library : https://github.com/CNMAT/OSC
 
 (c)20150709 iLabs for Smart Living with iPhone by Adrian Susianto

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>

byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED}; // Define Arduino MAC Address
byte  ip[] = {192,168,1,101};                 // Define Arduino local IP Address

int OutgoingPort = 8000;  // TouchOSC Outgoing Port
int IncomingPort = 9000;  // TouchOSC Incoming Port
int SwitchState  = HIGH;  // Declare Switch to OFF at the beginning (Active LOW State)
int DimmerState  = LOW;

int SwitchS1 = 36;  // Set Switch1 at pin 36
int SwitchS2 = 34;  // Set Switch2 at pin 34
int SwitchS3 = 32;  // Set Switch3 at pin 32
int SwitchS4 = 30;  // Set Switch4 at pin 30
int SwitchS5 = 28;  // Set Switch5 at pin 28
int SwitchS6 = 26;  // Set Switch6 at pin 26
int SwitchS7 = 24;  // Set Switch7 at pin 24
int SwitchS8 = 22;  // Set Switch8 at pin 22

int DimmerD1 = 23;  // Set Dimmer1 at pin 23
int DimmerD2 = 25;  // Set Dimmer2 at pin 25
int DimmerD3 = 27;  // Set Dimmer3 at pin 27
int DimmerD4 = 29;  // Set Dimmer4 at pin 29
int DimmerD5 = 31;  // Set Dimmer5 at pin 31
int DimmerD6 = 33;  // Set Dimmer6 at pin 33
int DimmerD7 = 35;  // Set Dimmer7 at pin 35
int DimmerD8 = 37;  // Set Dimmer8 at pin 37

EthernetUDP Udp;    // Create UDP message object

void setup()
{
  Ethernet.begin(mac, ip);                                   // Define local IP Address
  Udp.begin(OutgoingPort);                                   // Start the Ethernet connection

  pinMode(SwitchS1, OUTPUT); digitalWrite(SwitchS1, HIGH);   // Set Switch1 as Output and reset it
  pinMode(SwitchS2, OUTPUT); digitalWrite(SwitchS2, HIGH);   // Set Switch2 as Output and reset it
  pinMode(SwitchS3, OUTPUT); digitalWrite(SwitchS3, HIGH);   // Set Switch3 as Output and reset it
  pinMode(SwitchS4, OUTPUT); digitalWrite(SwitchS4, HIGH);   // Set Switch4 as Output and reset it
  pinMode(SwitchS5, OUTPUT); digitalWrite(SwitchS5, HIGH);   // Set Switch5 as Output and reset it
  pinMode(SwitchS6, OUTPUT); digitalWrite(SwitchS6, HIGH);   // Set Switch6 as Output and reset it
  pinMode(SwitchS7, OUTPUT); digitalWrite(SwitchS7, HIGH);   // Set Switch7 as Output and reset it
  pinMode(SwitchS8, OUTPUT); digitalWrite(SwitchS8, HIGH);   // Set Switch8 as Output and reset it

  pinMode(DimmerD1, OUTPUT); digitalWrite(DimmerD1, LOW);    // Set Dimmer1 as Output and reset it
  pinMode(DimmerD2, OUTPUT); digitalWrite(DimmerD2, LOW);    // Set Dimmer2 as Output and reset it
  pinMode(DimmerD3, OUTPUT); digitalWrite(DimmerD3, LOW);    // Set Dimmer3 as Output and reset it
  pinMode(DimmerD4, OUTPUT); digitalWrite(DimmerD4, LOW);    // Set Dimmer4 as Output and reset it
  pinMode(DimmerD5, OUTPUT); digitalWrite(DimmerD5, LOW);    // Set Dimmer5 as Output and reset it
  pinMode(DimmerD6, OUTPUT); digitalWrite(DimmerD6, LOW);    // Set Dimmer6 as Output and reset it
  pinMode(DimmerD7, OUTPUT); digitalWrite(DimmerD7, LOW);    // Set Dimmer7 as Output and reset it
  pinMode(DimmerD8, OUTPUT); digitalWrite(DimmerD8, LOW);    // Set Dimmer8 as Output and reset it
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
      msgIN.route("/lighting/l1",L1Data);               // Is it from Switch1 ?
      msgIN.route("/lighting/l2",L2Data);               // Is it from Switch2 ?
      msgIN.route("/lighting/l3",L3Data);               // Is it from Switch3 ?
      msgIN.route("/lighting/l4",L4Data);               // Is it from Switch4 ?
      msgIN.route("/lighting/l5",L5Data);               // Is it from Switch5 ?
      msgIN.route("/lighting/l6",L6Data);               // Is it from Switch6 ?
      msgIN.route("/lighting/l7",L7Data);               // Is it from Switch7 ?
      msgIN.route("/lighting/l8",L8Data);               // Is it from Switch8 ?  

      msgIN.route("/lighting/d1",D1Data);               // Is it from Dimmer1 ?
//      msgIN.route("/lighting/d2",D2Data);               // Is it from Dimmer2 ?
//      msgIN.route("/lighting/d3",D3Data);               // Is it from Dimmer3 ?
//      msgIN.route("/lighting/d4",D4Data);               // Is it from Dimmer4 ?
//      msgIN.route("/lighting/d5",D5Data);               // Is it from Dimmer5 ?
//      msgIN.route("/lighting/d6",D6Data);               // Is it from Dimmer6 ?
//      msgIN.route("/lighting/d7",D7Data);               // Is it from Dimmer7 ?
//      msgIN.route("/lighting/d8",D8Data);               // Is it from Dimmer8 ?  

      msgIN.route("/lighting/dimmer1",DimmerData1);     // Is it from Dimmer1 ?
      msgIN.route("/lighting/dimmer2",DimmerData2);     // Is it from Dimmer2 ?
      msgIN.route("/lighting/reset",Reset);             // Is it Reset Command ?
    }
  }
}

void L1Data(OSCMessage &msg, int)                       // If from Switch1 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS1, SwitchState);              // Send Switch1 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Main Gate ON");        // Set Character Message to display
  else msgOUT.add("Main Gate OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L2Data(OSCMessage &msg, int)                       // If from Switch2 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS2, SwitchState);              // Send Switch2 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Terrace ON");          // Set Character Message to display
  else msgOUT.add("Terrace OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L3Data(OSCMessage &msg, int)                       // If from Switch3 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS3, SwitchState);              // Send Switch3 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Car Port ON");         // Set Character Message to display
  else msgOUT.add("Car port OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L4Data(OSCMessage &msg, int)                       // If from Switch4 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS4, SwitchState);              // Send Switch4 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Garden ON");           // Set Character Message to display
  else msgOUT.add("Garden OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L5Data(OSCMessage &msg, int)                       // If from Switch5 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS5, SwitchState);              // Send Switch5 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Living Room ON");      // Set Character Message to display
  else msgOUT.add("Living Room OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L6Data(OSCMessage &msg, int)                       // If from Switch6 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS6, SwitchState);              // Send Switch6 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Dining Room ON");      // Set Character Message to display
  else msgOUT.add("Dining Room OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L7Data(OSCMessage &msg, int)                       // If from Switch7 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS7, SwitchState);              // Send Switch7 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Kitchen ON");          // Set Character Message to display
  else msgOUT.add("Kitchen OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void L8Data(OSCMessage &msg, int)                       // If from Switch8 then
{
  SwitchState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  digitalWrite(SwitchS8, SwitchState);              // Send Switch8 as incoming Control from TouchOSC 
  SwitchState = !SwitchState;                       // Inverse OSC Message because Relay Module use Low Level trigger
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (SwitchState) msgOUT.add("Upstair ON");          // Set Character Message to display
  else msgOUT.add("Upstair OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}

void D1Data(OSCMessage &msg, int)                       // If from Switch1 then
{
  DimmerState = (boolean) msg.getFloat(0);            // Get Data and store as Boolean Mode
  digitalWrite(DimmerD1, DimmerState);              // Send Switch1 as incoming Control from TouchOSC 
  OSCMessage msgOUT("/lighting/display");               // Define TouchOSC Control for Display
  if (DimmerState) msgOUT.add("Dimmer 1 ON");        // Set Character Message to display
  else msgOUT.add("Dimmer 2 OFF");               
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);        // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                                     // Send OSC message to TouchOSC
  Udp.endPacket();                                      // Send End Message signature
  msgOUT.empty();                                       // Set Free space occupied by message
}



void DimmerData1(OSCMessage &msg, int)            // If from Dimmer1 then
{
  int dimmer1 = msg.getFloat(0);                  // Store Incoming Message to variable
  OSCMessage msgOUT("/lighting/dimmer1data");     // Define which TouchOSC Control to send with Message
  msgOUT.add(dimmer1);                            // Define Message from Variable dimer1
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void DimmerData2(OSCMessage &msg, int)            // If from Dimmer2 then
{
  int dimmer2 = msg.getFloat(0);                  // Store Incoming Message to variable
  OSCMessage msgOUT("/lighting/dimmer2data");     // Define which TouchOSC Control to send with Message
  msgOUT.add(dimmer2);                            // Define Message from Variable dimer2
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
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
  ResetDimmer1();                                 // Send fader1 back to initial state at 0
  ResetDimmer1DataDisplay();                      // Reset Dimmer1 Data Display to 0
  ResetDimmer2();                                 // Send fader2 back to initial state at 0
  ResetDimmer2DataDisplay();                      // Reset Dimmer2 Data Display to 0
  delay(200);                                     // Hold a moment
  ResetLedOFF();                                  // Turn Reset Indicator OFF
  DisplayStatusOK();                              // Display all done and System OK
}

void ResetTouchOSCL1()                            // Resetting Light1 Control
{
  digitalWrite(SwitchS1, HIGH);                  // Turn OFF Switch1 Relay
  OSCMessage msgOUT("/lighting/l1");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL2()                            // Resetting Light2 Control
{
  digitalWrite(SwitchS2, HIGH);                  // Turn OFF Switch2 Relay
  OSCMessage msgOUT("/lighting/l2");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL3()                            // Resetting Light3 Control
{
  digitalWrite(SwitchS3, HIGH);                  // Turn OFF Switch3 Relay
  OSCMessage msgOUT("/lighting/l3");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL4()                            // Resetting Light4 Control
{
  digitalWrite(SwitchS4, HIGH);                  // Turn OFF Switch4 Relay
  OSCMessage msgOUT("/lighting/l4");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL5()                            // Resetting Light5 Control
{
  digitalWrite(SwitchS5, HIGH);                  // Turn OFF Switch5 Relay
  OSCMessage msgOUT("/lighting/l5");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL6()                            // Resetting Light6 Control
{
  digitalWrite(SwitchS6, HIGH);                  // Turn OFF Switch6 Relay
  OSCMessage msgOUT("/lighting/l6");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL7()                            // Resetting Light7 Control
{
  digitalWrite(SwitchS7, HIGH);                  // Turn OFF Switch7 Relay
  OSCMessage msgOUT("/lighting/l7");              // Define which TouchOSC Control to be Reset
  msgOUT.add(0);                                  // Define the Reset Data
  Udp.beginPacket(Udp.remoteIP(), IncomingPort);  // Prepare UDP Port with Message Data
  msgOUT.send(Udp);                               // Send OSC message to TouchOSC
  Udp.endPacket();                                // Send End Message signature
  msgOUT.empty();                                 // Set Free space occupied by message
}

void ResetTouchOSCL8()                            // Resetting Light8 Control
{
  digitalWrite(SwitchS8, HIGH);                  // Turn OFF Switch8 Relay
  OSCMessage msgOUT("/lighting/l8");              // Define which TouchOSC Control to be Reset
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
