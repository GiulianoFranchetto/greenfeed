#include <UsbComm.h>
#include <Regulateur.h>
#include <parson/parson.h>

using namespace std;

UsbComm usb_lora;
UsbComm usb_can;
Regulateur regulateur;
pthread_t thread_MPPT;
pthread_t thread_LORA;
pthread_t thread_CAN;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void *envoi_MPPT_LoRa (NOTHING)
{
  char buffer[100];
  float Vbat = 0;
  float Ibat = 0;
  float Mppt_i = 0;
  float Mppt_o = 0;

  while (1)
    {
      memset (buffer, '\0', 100);
      regulateur.lireTensionBatterie (Vbat);
      sleep (1);
      regulateur.lireIntensiteBatterie (Ibat);
      sleep (1);
      regulateur.lireMpptIn (Mppt_i);
      sleep (1);
      regulateur.lireMpptOut (Mppt_o);
      sleep (1);
      sprintf (buffer, "{\"abri\":{\"v_bat\": %.2f, \"p_bat\": %.2f, \"mppt_i\": %.2f, \"mppt_o\": %.2f}}", Vbat,
               Vbat * Ibat, Mppt_i, Mppt_o);
      usb_lora.envoyerMessage (buffer, false);
      sleep (60 * 15);
    }
}
#pragma clang diagnostic pop

void *manage_CAN (NOTHING)
{
  char mess_from_can[BUFF_SIZE];
  while (1)
    {
      size_t length;
      memset (mess_from_can, 0, BUFF_SIZE);
      if ((length = usb_can.recevoirMessage (mess_from_can)) > 0)
        {
          mess_from_can[length - 2] = 0;
          cout << "Message from CAN: " << mess_from_can << endl;
          char message_booking[200];
          sprintf (message_booking, "{\"demande\":{\"uid\":\"%s\"}}", mess_from_can);
          usb_lora.envoyerMessage (message_booking, false);
        }
    }

}

void *manage_LORA (NOTHING)
{
  char mess_from_lora[BUFF_SIZE];
  while (1)
    {
      memset (mess_from_lora, 0, BUFF_SIZE);
      if (usb_lora.recevoirMessage (mess_from_lora) > 0)
        {
          cout << "Message from LoRa gateway: " << mess_from_lora << endl;
          JSON_Value *root_value = json_parse_string (mess_from_lora);
          JSON_Object *root_object = json_value_get_object (root_value);
          int authorized = (int) json_object_get_number (root_object, "authorize");
          if (authorized)
            {
              char buf[4];
              int velo = (int) json_object_get_number (root_object, "velo");
              sprintf (buf, "1;%d", velo);
              cout << "Sending " << buf << " to Arduino CAN" << endl;
              usb_can.envoyerMessage (buf, false);
            }
          json_value_free (root_value);
        }
    }
}

int main (int arcg, char **argv)
{
  if (arcg != 4)
    {
      cout << "Usage: ./rpi_final lora_interface can_interface mppt_interface" << endl;
      exit (EXIT_FAILURE);
    }

  string lora_interface;
  string can_interface;

  lora_interface = argv[1];
  can_interface = argv[2];
  regulateur.connexion (argv[3]);

  pthread_create (&thread_MPPT, NULL, envoi_MPPT_LoRa, NULL);
  int res_usb_lora = usb_lora.ouvrirCommunication (lora_interface);
  if (res_usb_lora < 0)
    {
      cout << "Couldn't connect to the LoRa Arduino. Exiting" << endl;
      exit (-1);
    }
  int res_usb_can = usb_can.ouvrirCommunication (can_interface);
  cout << "Can operationnel:" << (res_usb_can > 0) << endl;
  sleep (1);
  pthread_create (&thread_CAN, 0, manage_CAN, NULL);
  pthread_create (&thread_LORA, 0, manage_LORA, NULL);

  usb_lora.envoyerMessage ((char *) "{\"rpi\": \"starting\"}", false);

  pthread_join (thread_CAN, NULL);
  return 0;

}