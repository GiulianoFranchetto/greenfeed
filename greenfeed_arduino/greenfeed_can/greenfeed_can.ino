#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <SPI.h>

INT8U len = 0;
INT8U buf[8];
String inputString;

MCP_CAN CAN(9);                                          
 
void setup()
{
    Serial.begin(9600);

START_INIT:

   if(CAN_OK == CAN.begin(CAN_100KBPS))                   
        CAN.setMode(MODE_LISTENONLY); 
   else
   {
       delay(100);
       goto START_INIT;
   }
}

boolean string_presente = false;

long createSID(byte borne, byte cmd)
{
    borne = borne+1;
    return ( ( borne<< 6) + cmd);
}

byte getNumBorne(long SID){
   return (SID >>5)-1;
}

byte getNumCmd(long SID, byte borne){
    return SID - ((borne+1)<<6);
}

byte charToInt(char d)
{
    char str[2];
    str[0] = d;
    str[1]='\0';
   return (int) strtol(str, NULL, 8);
}
void loop()
{
   byte borneID;
   if(CAN_MSGAVAIL == CAN.checkReceive())           
    {
        CAN.readMsgBuf(&len, buf);  
        INT32U id = CAN.getCanId();
        byte borneID = getNumBorne(id);
        String data = "";
        for(int i = 0; i<len; i++)   
        {
            data+=buf[i]+";";
        }
        if(id == 0x49) Serial.println(data);

    }
    
    while (Serial.available() > 0 ) {
      char inChar = Serial.read(); 
      if(inChar == '\n'){
        string_presente = true;
        break;
      }
      inputString += inChar;
    }
    
    if(string_presente){
      CAN.setMode(MODE_NORMAL);
      delay(100);
      if(inputString == "0;"){}
      else if(inputString.charAt(0) == '1'){
        byte num = charToInt(inputString.charAt(2));
        CAN.sendMsgBuf(createSID(num,0x07), 0, num, 0, 0);
      }
      string_presente = false;   
      inputString="";    
      CAN.setMode(MODE_LISTENONLY);  
    }
    
    delay(100);  
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
