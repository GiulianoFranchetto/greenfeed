#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SPI.h>

MCP_CAN CAN(9);                                          


void setup()
{
  Serial.begin(9600);
  while(CAN_OK != CAN.begin(CAN_100KBPS))                   
  {
    delay(100);
  }
}

int get_n_first_bits(unsigned int number, unsigned int bit)
{
  unsigned  mask;
  mask = ((1 << bit) - 1);
  return number & mask;
}

void split_sid(uint32_t sid, uint8_t *cmd, uint8_t *id)
{
  *cmd = get_n_first_bits(sid, 6);
  *id = sid >> 6;
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[12];
    uint32_t sid;
    uint8_t command, borne_id;

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        sid = CAN.getCanId();
        split_sid(sid, &command, &borne_id);
        Serial.println("-----------------------------");
        Serial.print("La borne ");
        Serial.print(borne_id, HEX);
        Serial.print(" a envoyé la commande ");
        Serial.println(command, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();
    }
}


