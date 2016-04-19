/**
    \file UsbComm.h
    \author Giuliano Franchetto
    \version 1.0
    \date 31/03/2015

    \brief Ce fichier déclare la classe qui va gérer la communication entre la Raspberry et l'Arduino
    Dans la version 1.0 : cette classe ne gère que le lien Arduino -> RPi concernant l'envoi en LoRa.
    La partie CAN sera faite quand le shield aura été reéu

    Cette classe s'appuie sur les entétes systéme de Linux. En effetm une communication USB n'est en fait que l'écriture dans
    un fichier, car tout n'est que fichier en Linux. La communication a un baudrate de 9600 fixé. Si, pour une raison quelconque,
    ce baudrate doit étre changé, IL FAUT AUSSI PENSER A LE CHANGER DANS LE CODE DE L'ARDUINO.
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
#define usb_r   ssize_t /*!< Déclare un nouveau type qui représentera le résultat d'une opération en USB*/
#define usb_interface int /*!< Déclare un nouveau type qui représentera le fichier dans lequel sera écrit les données é envoyer en USB*/
#define USB_BAUDRATE    B9600 /*!< Le baudrate du l'USB*/
#define BUFF_SIZE   200

/**
    \namespace std
*/
using namespace std;

/**
    \class UsbComm
    \brief Cette classe regroupe toutes les fonctions haut niveau afin d'ouvrir une communication USB entre deux appareils et envoyer des
    données
*/
class UsbComm {
 public:
  /*!
     \brief Constructeur par défaut

     Constructeur par défaut de la classe UsbComm
   */
  UsbComm ();

  /*!
     \brief Ouvre la communication en USB

     Cette méthode initialise la communication en USB

     \param const string phy_interface : l'interface physique de l'USB (classiquement /dev/ttyACM0)
     \return 0 si tout va bien,
     -1 sinon
  */
  usb_r ouvrirCommunication (const string);

  /*!
     \brief Envoie une donnée en USB

     Cette méthode envoie une donnée en USB. Si le message n'est pas terminé par "\n", alors ce caractére
     est rajouter automatiquement.

     \param char* message : le message é envoyer
     \param bool changeInB64 : if set to true, the char* in parameter will be converted to Base64 string
     \return 0 si tout va bien,
     -1 sinon
  */
  usb_r envoyerMessage (char *, bool);

  /*!
      \brief Reéoit une donnée en USB

      \param char* message : buffer dans lequel le message sera mis
      \return 0 si rien n'a été lu,
      -1 si erreur
   */
  usb_r recevoirMessage (char *);

  /*!
     \brief Destructeur de la classe UsbComm

     Cette méthode détruit l'objet UsbComm, ferme la connexion USB et libére la mémoire.
   */
  virtual ~UsbComm ();
 protected:
 private:
  usb_interface interface; /*!< Le fichier représentant la connection USB*/
};

#endif // USBCOMM_H
