#include <SPI.h>

/**
LORA FUNCTIONS
**/

const int slaveSelectPin = 10;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;

void startSPI(){
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV64);
}

void LoRa_init() {
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin,HIGH); 
  // initialize SPI:
  startSPI();
  delay(1000);
  // Wait SPI to be ready
}

void LoRa_send(String in) {

  int len = in.length();

 digitalWrite(slaveSelectPin,LOW);

  //  send data
  SPI.transfer(0x02);
  delay(1);
  SPI.transfer(len >> 8);
  delay(1);
  SPI.transfer(len & 0xFF);
  delay(1);
  for (int i=0; i<len; i++) {
    SPI.transfer(in.charAt(i));
  delay(1);
  }

  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 
 
  delay(100);
}

int LoRa_available(){
  int available_msb;
  int available_lsb;
  int available;

  digitalWrite(slaveSelectPin,LOW);

  //  data available cmd
  SPI.transfer(0x00);
  delay(1);
  SPI.transfer(0x00);
  delay(1);
  available_msb = SPI.transfer(0x00);
  delay(1);
  available_lsb = SPI.transfer(0x00);
  delay(1);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 

  delay(1);

  available = (available_msb<<8) + available_lsb;

  return available;
}

char LoRa_read() {

  byte c;
  digitalWrite(slaveSelectPin,LOW);          

  //  read data
  SPI.transfer(0x01);
  delay(1);
  SPI.transfer(0x00);
  delay(1);
  c = SPI.transfer(0x00);
  delay(1);

  digitalWrite(slaveSelectPin,HIGH); 
  delay(1);

  return c;
 
}

// Change radio configuration: 0 to 3
// 0 is the fastest but less robust
// 3 is the slowest but more robust (better distance)
void LoRa_RF_config(int in) {

  digitalWrite(slaveSelectPin,LOW);
  // CFG cmd
  SPI.transfer(0x05);
  delay(1);  
  SPI.transfer(0x00);
  delay(1);
  SPI.transfer(0x01);
  delay(1);
  SPI.transfer(in);
  delay(1);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 

  delay(100);
}

// Change radio frequency
// input is in Hz
// Range is 863 000 000 to 870 000 000
// Be careful of the band width used at band limits
void LoRa_freq(long f) {
  digitalWrite(slaveSelectPin,LOW);
  //  FREQ cmd
  SPI.transfer(0x04);
  delay(1);  
  SPI.transfer(0x00);
  delay(1);
  SPI.transfer(0x04);
  delay(1);
  SPI.transfer((f>>24) & 0xFF);
  delay(1);
  SPI.transfer((f>>16) & 0xFF);
  delay(1);
  SPI.transfer((f>>8) & 0xFF);
  delay(1);
  SPI.transfer(f & 0xFF);
  delay(1);
  
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin,HIGH); 

  delay(100);
  
}


// Pre implmented radio frequency channel configuration
// input is channel number
void LoRa_freq_channel(int nb) {
  switch(nb) {
    case 0:
      LoRa_freq(868000000);
    break;
    case 1:
      LoRa_freq(868100000);
    break;
    case 2:
      LoRa_freq(868200000);
    break;
    case 3:
      LoRa_freq(868300000);
    break;
    case 4:
      LoRa_freq(869500000);
    break;
    case 5:
      LoRa_freq(869600000);
    break;
    case 6:
      LoRa_freq(869800000);
    break;
    case 7:
      LoRa_freq(869900000);
    break;
  }
}

String getOrder(String message)
{
  String delimiter = "-";
  return message.substring(0, message.indexOf(delimiter));
}

uint8_t getBorneFromMessage(String message)
{
  String delimiter = "-";
  int pos = message.indexOf(delimiter);
  String s = message.substring(pos+1, message.indexOf(delimiter, pos+1));
  if(s=="1") return 0x01;
  if(s=="2") return 0x02;
  if(s=="3") return 0x03;
  
}

void setup()
{
    Serial.begin(9600);
    LoRa_init();
    LoRa_RF_config(3); //ex 0
    LoRa_freq_channel(3);
    delay(250);
}

void loop()
{
  int s;
  boolean loraComplete = false;
  
  /****************************************************/
  /**
  * In this condition, we are looking if there is any data
  * sent by the raspberry. If this is the case, we send it 
  * using LoRa protocol
  **/
  
  // Reading available data
  while (Serial.available() > 0 ) {
    char inChar = Serial.read(); 
    if(inChar == '\n'){
      stringComplete = true;
      break;
    } else {
      inputString += inChar;
    }
  }
  
  // Sending available data
  if (stringComplete) {
    LoRa_send(inputString);
    inputString = "";
    stringComplete = false;
  }
  
  
  /****************************************************/
  while(LoRa_available() > 0){
      char inLora = LoRa_read();
      s++;
      inputString += inLora;
      loraComplete = true;
  }
  
  if(loraComplete){
      char inLora_dec64[100];
      char tmp[100];
      inputString.toCharArray(tmp, s + 1);
      inputString= "";
      s=0;
      loraComplete = false;
  }
  
    delay(10);    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
