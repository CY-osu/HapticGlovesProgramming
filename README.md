# TouchTech - VR Haptic Gloves
This repo currently used for study and development of VR Haptic Gloves.

This repository contains a variety of programs, each crucial to the function of the VR test environment and the glove itself.
While the entire Unity environment is provided, these files could be useful for documentation and backup purposes.

TempMain.cs - This file opens serial communication between Unity and the client, and both generates and sends signals to the client
based on the input received from the user within the VR environment. The metadata file with the same name is also necessary, but is not
manually programmed. TempMain.cs is placed on the OVRCameraRig object, and references the temperature scripts!

coldScript.cs and heatScript.cs - Both act similarly, but correspond to the different coldBall and heatBall objects. These set public variables
based on input received from the user, and this variable is read by TempMain.cs to trigger signal generation. These are placed on the corresponding
coldBall and heatBall objects.

sketch_bleclient.ino - The code for the client end of communication between the two controllers. This program opens BLE between itself and the server,
receives data sent by Unity, and transmits that data over BLE to the server. This code goes on the client controller, which directly plugs into the
computer and has a "C" marked on the box.

sketch_bleserver.ino - The code for the server end of communication. This program also opens BLE between itself and the client, and receives the data that the
client transmits. Once the data is received, the handleCallback() function processes the data and performs various actions, namely activating LED and temperature
output. This code goes on the ESP32 soldered into the glove itself.

sketch_glovewired.ino - Should BLE not work properly, the glove can be used using a direct wired connection. This code does not open BLE, and simply reads data
sent from Unity, similar to the client, and processes it, similar to the server. If necessary, this code can be put on the ESP32 in the glove itself. Ideally, 
the BLE connection will work!
