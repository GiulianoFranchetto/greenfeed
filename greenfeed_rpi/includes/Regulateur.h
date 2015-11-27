/**
    \file Regulateur.h
    \author Giuliano Franchetto
    \version 1.1
    \date 18/03/2015

    \brief Ce fichier déclare la classe \see Regulateur, qui est la classe principale de ce programme
           avec \see UsbComm

    Cet entête déclare une nouvelle classe, ainsi que de nombreuses constantes. Ces constantes sont les addresses
    des registres du MPPT Tristar qui vont nous permettrent de récupérer les données électriques
    de l'abri vélo.
    Cette classe s'appuie sur la bibliothèque libmodus, qui permet de faire appel au protocole Modbus de façon
    assez simple.
    ATTENTION cependant : libmodbus est difficilement installable sur Windows. Ce projet est donc sensé être build sur
    une machine Linux ayant libmodbus installé (voir le fichier ReadME)
*/

#ifndef REGULATEUR_H
#define REGULATEUR_H

#include <modbus/modbus.h>
#include <string>

#define modbus_r            int /*!< Définition d'un nouveau type représentant le résultat d'une requête modbus */
#define addr                int /*!< Définition d'un nouveau type représentant une addresse de registre */

#define BAUDRATE            9600 /*!< Baudrate du MPPT TriStar */
#define PARITY              'N' /*!< Parité du MPPT Tristar */
#define DATA_BITS           8 /*!< Nombre de bits de données */
#define STOP_BITS           2 /*!< Nombre de bits de stop */

#define SERVER_ID       	0x01 /*!< Cette adresse est l'adresse slave par défaut du MPPT */

#define ADDRESS_V_PU_HI    	0x0000 /*!< Adresse de la partie entière de l'echelle de tension */
#define ADDRESS_V_PU_LO		0x0001 /*!< Adresse de la partie fractionnelle de l'échelle de tension */
#define ADDRESS_BAT_VAL		0x0019 /*!< Adresse de la valeur de la tension des batteries. Attention à bien appliquer l'échelle suivante : vbat * v_pu * 2^-15 */

#define ADDRESS_I_PU_HI     0x0002 /*!< Adresse de la partie entière de l'echelle de courant */
#define ADDRESS_BAT_I_VAL   0x001C /*!< Adresse de la valeur de l'intensité des batteries. Attention à bien appliquer l'échelle suivante : ibat * i_pu * 2^-15 */

#define ADDRESS_MPPT_OUT    0x003A /*!< Adresse de la valeur de sortie du MPPT. La loi pour convertir la valeur en W est : mppt_o * v_pu * i_pu * 0.1 */
#define ADDRESS_MPPT_IN     0x003B /*!< Adresse de la valeur de l'entrée du MPPT. La loi pour convertir la valeur en W est : mppt_i * v_pu * i_pu * 0.1 */

/**
    \namespace std
*/
using namespace std;

/**
    \class Regulateur
    \brief Cette classe regroupe toutes les fonctions haut niveau permettant de faire des appels
    en modbus sur le MPPT
*/
class Regulateur
{
    public:
        /*!
           \brief Constructeur par défaut

           Constructeur par défaut de la classe Regulateur
         */
        Regulateur();

        /*!
           \brief Lance la communication modbus

           Cette méthode permet d'initialiser la connexion avec le modbus. Elle doit être appelé avant n'importe quelle opération sur le modbus
         */
        modbus_r connexion(string);

        /*!
           \brief Lit la tension de la batterie

           Cette méthode lit la tension des batteries de l'abri vélo

           \param float& resultat : une référence vers une variable qui contiendra le résultat de la requête
           \return 0 si tout va bien,
           -1 sinon
         */
        modbus_r lireTensionBatterie(float&);

        /*!
           \brief Lit l'intensité de la batterie

           Cette méthode lit l'intensité des batteries de l'abri vélo

           \param float& resultat : une référence vers une variable qui contiendra le résultat de la requête
           \return 0 si tout va bien,
           -1 sinon
         */
        modbus_r lireIntensiteBatterie(float&);

        /*!
           \brief Lit la puissance générée par le MPPT

           Cette méthode lit la puissance générée par le MPPT

           \param float& resultat : une référence vers une variable qui contiendra le résultat de la requête
           \return 0 si tout va bien,
           -1 sinon
         */
        modbus_r lireMpptOut(float&);

        /*!
            \brief Lit la puissance à l'entrée du MPPT

            Cette méthode lit la puissance en entrée du MPPT

            \param float& resultat : une référence vers une variable qui contiendra le résultat de la requête
            \return 0 si tout va bien,
            -1 sinon
         */
        modbus_r lireMpptIn(float&);

        /*!
           \brief Destructeur de la classe Regulateur

           Cette méthode détruit l'objet Régulateur, ferme la connexion avec le modbus et libère la mémoire.
         */
        virtual ~Regulateur();
    protected:

    private:
        modbus_t* ctx; /*!< Pointeur vers le connecteur modbus */
        string physical_interface; /*!< Le nom de l'interface physique sur laquelle est connecté le modbus */
        bool connected; /*!< Etat de la connection du modbus */

        /*!
           \brief Lit un registre

           Cette méthode permet de lire un registre du MPPT. Cette méthode est PRIVÉE,
           afin d'éviter une lecture de registre interdite.
           Les fonctions haut niveau sont dans la partie PUBLIQUE

           \param addr adresse: l'adresse du registre
           \param uint16_t* resultat : pointeur vers le resultat de la requête modbus
           \return 0 si tout va bien,
           -1 sinon
         */
        modbus_r lireRegistre(const addr, uint16_t*);

        /*!
           \brief Ferme la connexion en modbus

           Cette méthode ferme la connexion en modbus, et libère la mémoire
           Cette fonction est PRIVÉE, car elle est appelée directement par le destructeur de la classe
         */
        void deconnexion();
};

#endif // REGULATEUR_H
