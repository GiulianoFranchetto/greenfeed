#include <CAN.h>
#include <SPI.h>

// ID numbers
#define IDWAITED 200
#define OWNID 0x183

// Create an instance of the object
CAN myCAN = CAN();

// Setting up our devices and I/Os
void setup() {
  // Initializes the UART
  Serial.begin(115200);
  delay(100);

  // Let's open the bus. Remember the input parameter:
  // 1: 1Mbps
  // 500: 500Kbps  <--- Most frequently used
  // 250: 250Kbp
  // 125: 125Kbps
  myCAN.begin(125);
}

void loop() {
  
  //****************************************
  // 1. Receive data
  //****************************************
  
  if (myCAN.messageAvailable() == 1) {
    // Read the last message received.
    myCAN.getMessage(&myCAN.messageRx);
    // Print in the serial monitor the received message
    myCAN.printMessage(&myCAN.messageRx);
  }
  

  //****************************************
  // 2. Send data
  //****************************************
  
  // Insert the ID in the data structure
  myCAN.messageTx.id = OWNID;
  // These fields include the data to send
  myCAN.messageTx.data[0] = 0;
  myCAN.messageTx.data[1] += 1;
  myCAN.messageTx.data[2] = 2;
  myCAN.messageTx.data[3] = 3;
  myCAN.messageTx.data[4] = 4;
  myCAN.messageTx.data[5] = 5;
  myCAN.messageTx.data[6] = 6;
  myCAN.messageTx.data[7] = 7;

  // The length of the data structure
  myCAN.messageTx.header.length = 8;
  // Send data
  myCAN.sendMessage(&myCAN.messageTx);  
  // A time delay
  delay(1000);
}
