/**
    \file UsbComm.h
    \author Giuliano Franchetto
    \version 1.0
    \date 31/03/2015

    \brief Ce fichier d�clare la classe qui va g�rer la communication entre la Raspberry et l'Arduino
    Dans la version 1.0 : cette classe ne g�re que le lien Arduino -> RPi concernant l'envoi en LoRa.
    La partie CAN sera faite quand le shield aura �t� re�u

    Cette classe s'appuie sur les ent�tes syst�me de Linux. En effetm une communication USB n'est en fait que l'�criture dans
    un fichier, car tout n'es tque fichier en Linux. La communication a un baudrate de 9600 fix�. Si, pour une raison quelconque,
    ce baudrate doit �tre chang�, IL FAUT AUSSI PENSER A LE CHANGER DANS LE CODE DE L'ARDUINO.
*/

#ifndef USBCOMM_H
#define USBCOMM_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <termios.h>
#include <string>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NOTHING void* rien
#define usb_r   int /*!< D�clare un nouveau type qui repr�sentera le r�sultat d'une op�ration en USB*/
#define usb_interface int /*!< D�clare un nouveau type qui repr�sentera le fichier dans lequel sera �crit les donn�es � envoyer en USB*/
#define USB_BAUDRATE    B9600 /*!< Le baudrate du l'USB*/
#define BUFF_SIZE   200

/**
    \namespace std
*/
using namespace std;

/**
    \class UsbComm
    \brief Cette classe regroupe toutes les fonctions haut niveau afin d'ouvrir une communication USB entre deux appareils et envoyer des
    donn�es
*/
class UsbComm {
 public:
  /*!
     \brief Constructeur par d�faut

     Constructeur par d�faut de la classe UsbComm
   */
  UsbComm ();

  /*!
     \brief Ouvre la communication en USB

     Cette m�thode initialise la communication en USB

     \param const string phy_interface : l'interface physique de l'USB (classiquement /dev/ttyACM0)
     \return 0 si tout va bien,
     -1 sinon
  */
  usb_r ouvrirCommunication (const string);

  /*!
     \brief Envoie une donn�e en USB

     Cette m�thode envoie une donn�e en USB. Si le message n'est pas termin� par "\n", alors ce caract�re
     est rajouter automatiquement.

     \param char* message : le message � envoyer
     \param bool changeInB64 : if set to true, the char* in parameter will be converted to Base64 string
     \return 0 si tout va bien,
     -1 sinon
  */
  usb_r envoyerMessage (char *, bool);

  /*!
      \brief Re�oit une donn�e en USB

      \param char* message : buffer dans lequel le message sera mis
      \return 0 si rien n'a �t� lu,
      -1 si erreur
   */
  usb_r recevoirMessage (char *);

  /*!
     \brief Destructeur de la classe UsbComm

     Cette m�thode d�truit l'objet UsbComm, ferme la connexion USB et lib�re la m�moire.
   */
  virtual ~UsbComm ();
 protected:
 private:
  usb_interface interface; /*!< Le fichier repr�sentant la connection USB*/
};

#endif // USBCOMM_H
