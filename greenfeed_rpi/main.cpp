#include <UsbComm.h>
#include <Regulateur.h>
#include <unistd.h>

using namespace std;

UsbComm usb_lora;
UsbComm usb_can;
Regulateur regulateur;
pthread_t thread_MPPT;

void* envoi_MPPT_LoRa(NOTHING)
{
    char buffer[100];
    float Vbat = 0;
    float Ibat = 0;
    float Mppt_i = 0;
    float Mppt_o = 0;

    while(1) {
        memset(buffer, '\0', 100);
        regulateur.lireTensionBatterie(Vbat);
        sleep(1);
        regulateur.lireIntensiteBatterie(Ibat);
        sleep(1);
        regulateur.lireMpptIn(Mppt_i);
        sleep(1);
        regulateur.lireMpptOut(Mppt_o);
        sleep(1);
        sprintf(buffer, "{\"abri\":{\"v_bat\": %.2f, \"p_bat\": %.2f, \"mppt_i\": %.2f, \"mppt_o\": %.2f}}", Vbat, Vbat * Ibat, Mppt_i, Mppt_o);
        usb_lora.envoyerMessage(buffer, false);
        sleep(60 * 15);
    }
}

int main(int arcg, char** argv)
{
    if(arcg != 4){
        cout << "Usage: ./rpi_final lora_interface can_interface mppt_interface" << endl;
        exit(EXIT_FAILURE);
    }

    string lora_interface;
    string can_interface;

    lora_interface=argv[1];
    can_interface=argv[2];
    regulateur.connexion(argv[3]);

    pthread_create(&thread_MPPT, NULL, envoi_MPPT_LoRa, NULL);
    int res_usb_lora = usb_lora.ouvrirCommunication(lora_interface);
    if(res_usb_lora != 0){
        cout << "Couldn't connect to the LoRa Arduino. Exiting" << endl;
        exit(-1);
    }
    int res_usb_can = usb_can.ouvrirCommunication(can_interface);

    sleep(1);
    usb_lora.envoyerMessage((char*)"{\"rpi\": \"starting\"}", false);

    while(1)
    {
       if(res_usb_lora == 0 && res_usb_can == 0)
        {

            char* mess_from_can = (char*)malloc(BUFF_SIZE);
		    char* mess_from_lora = (char*)malloc(BUFF_SIZE);

		    if(usb_lora.recevoirMessage(mess_from_lora)>0) {
		       usb_can.envoyerMessage(mess_from_lora, false);
		       cout << "Message : " << mess_from_lora << endl;
		    }
		    free(mess_from_lora);

	        /*if(usb_can.recevoirMessage(mess_from_can)>0) {
	            usb_lora.envoyerMessage(mess_from_can, true);
		    }*/
			free(message_from_can);
		    usleep(1000 * 100);
    }

    return 0;
}
