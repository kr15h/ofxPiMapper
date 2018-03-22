# Remote Control Server for ofxPiMapper

This example demonstrates a TCP server for ofxPiMapper remote control. The other part of this is the [Remote Control Client](../). What it does is the following.

- It creates a `TCPServer` singleton.
- Waits for a client to connect via TCP.
- Sends ofxPiMapper configuration once client is connected.
- Accepts keyboard and mouse events from client after.
- Forwards events to ofxPiMapper instance.

In a real-world scenario, the server should reside on the Raspberry Pi side of your installation. The Raspberry Pi should be connected to wired or wireless network. An IP address should be set. 

The client should know the following.

- The **IP address** of the Raspberry Pi with the server.
- The port, which is **9999** in this case.
