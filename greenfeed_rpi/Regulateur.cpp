#include <Regulateur.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>

using namespace std;

Regulateur::Regulateur()
{
    connected = false;
    physical_interface = "/dev/ttyUSB0";
}

Regulateur::~Regulateur()
{
    this->deconnexion();
}

modbus_r Regulateur::connexion(string interface)
{
    this->physical_interface = interface;
    this->ctx = modbus_new_rtu(physical_interface.c_str(), BAUDRATE, PARITY, DATA_BITS, STOP_BITS);

    modbus_set_slave(ctx, SERVER_ID);

    if (modbus_connect(this->ctx) == -1) {
        cout << "Connexion echouee: " << modbus_strerror(errno) << endl;
        modbus_free(this->ctx);
        return -1;
    }
    connected = true;
    return 0;
}

void Regulateur::deconnexion()
{
if(connected)
    {
        modbus_close(ctx);
        modbus_free(ctx);
    }
}


modbus_r Regulateur::lireRegistre(const addr ad, uint16_t* destination)
{
    int rc = modbus_read_registers(this->ctx, ad, 1, destination);
    if (rc != 1) {
        cout << "ERROR modbus_read_registers " << rc << endl;
        cout << "Address = " << ad <<endl;
        return -1;
    }
    return 0;

}

modbus_r Regulateur::lireTensionBatterie(float& resultat)
{
    uint16_t *v_pu = (uint16_t*)malloc(sizeof(uint16_t));
    memset(v_pu, 0, sizeof(uint16_t));

    uint16_t *v_bat = (uint16_t*)malloc(sizeof(uint16_t));
    memset(v_bat, 0, sizeof(uint16_t));

    if(lireRegistre(ADDRESS_V_PU_HI, v_pu) != 0)
        return -1;

    sleep(1);

    if(lireRegistre(ADDRESS_BAT_VAL, v_bat) != 0)
        return -1;

    float voltage_scaler = (float)v_pu[0];
    float bat_reg_float = (float)v_bat[0];
    resultat = (float)(bat_reg_float * voltage_scaler) / 32768;

    free(v_bat);
    free(v_pu);

    return 0;
}

modbus_r Regulateur::lireIntensiteBatterie(float& resultat)
{
    uint16_t *i_pu = (uint16_t*)malloc(sizeof(int16_t));
    memset(i_pu, 0, sizeof(int16_t));

    uint16_t *i_bat = (uint16_t*)malloc(sizeof(uint16_t));
    memset(i_bat, 0, sizeof(uint16_t));

    if(lireRegistre(ADDRESS_I_PU_HI, i_pu) != 0)
        return -1;

    sleep(1);

    if(lireRegistre(ADDRESS_BAT_I_VAL, i_bat) != 0)
        return -1;

    float intensite_scaler = i_pu[0];
    float bat_reg_float = (float)i_bat[0];
    resultat = (float)(bat_reg_float * intensite_scaler) / 32768;

    free(i_bat);
    free(i_pu);

    return 0;
}

modbus_r Regulateur::lireMpptOut(float& resultat)
{
    uint16_t *mppt_pu = (uint16_t*)malloc(sizeof(int16_t));
    memset(mppt_pu, 0, sizeof(int16_t));

    uint16_t *v_pu = (uint16_t*)malloc(sizeof(uint16_t));
    memset(v_pu, 0, sizeof(uint16_t));

    uint16_t *i_pu = (uint16_t*)malloc(sizeof(int16_t));
    memset(i_pu, 0, sizeof(int16_t));


    if(lireRegistre(ADDRESS_I_PU_HI, i_pu) != 0)
        return -1;

    if(lireRegistre(ADDRESS_V_PU_HI, v_pu) != 0)
        return -1;

    if(lireRegistre(ADDRESS_MPPT_OUT, mppt_pu) != 0)
        return -1;

    sleep(1);

    resultat = (float)mppt_pu[0] * v_pu[0] * i_pu[0] / (131072);

    free(mppt_pu);
    free(v_pu);
    free(i_pu);

    return 0;
}

modbus_r Regulateur::lireMpptIn(float& resultat)
{
    uint16_t *mppt_pu = (uint16_t*)malloc(sizeof(int16_t));
    memset(mppt_pu, 0, sizeof(int16_t));

    uint16_t *v_pu = (uint16_t*)malloc(sizeof(uint16_t));
    memset(v_pu, 0, sizeof(uint16_t));

    uint16_t *i_pu = (uint16_t*)malloc(sizeof(int16_t));
    memset(i_pu, 0, sizeof(int16_t));


    if(lireRegistre(ADDRESS_I_PU_HI, i_pu) != 0)
        return -1;

    if(lireRegistre(ADDRESS_V_PU_HI, v_pu) != 0)
        return -1;

    if(lireRegistre(ADDRESS_MPPT_IN, mppt_pu) != 0)
        return -1;

    sleep(1);

    resultat = (float)mppt_pu[0] * v_pu[0] * i_pu[0] / (131072);

    free(mppt_pu);
    free(v_pu);
    free(i_pu);

    return 0;
}
