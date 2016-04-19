#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SPI.h>

#define DEBUG

#ifdef DEBUG
#define print_debug(message, ...)            Serial.print(message, ##__VA_ARGS__)
#define println_debug(message, ...)          Serial.println(message, ##__VA_ARGS__)
#else
#define print_debug(message, ...)
#define println_debug(message, ...)
#endif

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

long createSID(byte borne, byte cmd)
{
    borne = borne + 1;
    return ( (borne << 6) + cmd);
}

byte charToInt(char d)
{
    char str[2];
    str[0]=d;
    str[1]=0;
    return (int) strtol(str, NULL, 8);
}

uint8_t a[8];
void loop()
{
    byte borneID;
    uint8_t len = 0, buf[8];
    String inputString;
    boolean string_presente = false;
    
    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf);
        INT32U id = CAN.getCanId();
        print_debug("New message with command ");
        println_debug(id, HEX);
        
        for(int i = 0; i<len; i++)
        {
            print_debug(buf[i], HEX);
            print_debug("  ");
        }
        println_debug();
        
        if(id == 0x49) {
            Serial.println(buf+1);
        }
    }
    
    while (Serial.available() > 0 ) {
        char inChar = Serial.read();
        inputString += inChar;
        string_presente = true;
    }
    if(string_presente){
        CAN.setMode(MODE_NORMAL);
        delay(100);
        print_debug("Message from Raspi: ");
        println_debug(inputString);
        
        byte num = charToInt(inputString.charAt(2));
        /* Message 1: authorized */
        if(inputString.charAt(0) == '1'){
            uint8_t fake_name[8] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
            CAN.sendMsgBuf(createSID(num,0x0F), 0, num, 8, fake_name);
        }
        /* Message 2: get parameters */
        else if(inputString.charAt(0) == '2'){
            CAN.sendMsgBuf(createSID(num,0x14), 0, num, 0, 0);
        } 
        /* Message 3: set parameters */
        else if(inputString.charAt(0) == '3'){    
            uint8_t aa [8] = {0x09, 0x05, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00};
            CAN.sendMsgBuf(createSID(num,0x12), 0, num, 8, aa);
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
