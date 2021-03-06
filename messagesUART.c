/**************************************************************************
Version 1.
 
Auteur : Hugo Therrien
Date de cr�ation : 12/2017
 
Description : Fichier de d�codage et d'encodage des messages
Propri�t� Les S de Sherbrooke
**************************************************************************/

#include "messagesUART.h"
#include "cobs.h"
#include "crc8.h"
#include "assert.h"

#define TAILLE_TAMPON_ENCODAGE 32
#define TAILLE_TAMPON_DECODAGE TAILLE_TAMPON_ENCODAGE

static uint8_t tamponEncodage[TAILLE_TAMPON_ENCODAGE] = {0};
static uint8_t tamponDecodage[TAILLE_TAMPON_DECODAGE] = {0};

uint8_t* encoderAccel(DonneeAccel* donnee)
{   
    donnee->header = MESSAGE_ACCEL;
    cobsEncode((uint8_t *)donnee, TAILLE_MESSAGE_ACCEL, tamponEncodage);
    return tamponEncodage;
}

uint8_t* encoderAccelCRC(DonneeAccelCRC* donnee)
{
    donnee->header = MESSAGE_ACCEL_CRC;
    donnee->crc8 = ComputeCRC8((uint8_t*) donnee, TAILLE_MESSAGE_ACCEL_CRC);
    cobsEncode((uint8_t *)donnee, TAILLE_MESSAGE_ACCEL_CRC + 1, tamponEncodage);
    return tamponEncodage;
}

void* decoderMessage(uint8_t* message, uint8_t taille, const uint8_t typeAttendu)
{
    uint8_t header;
    assert(taille < TAILLE_TAMPON_DECODAGE);
    cobsDecode(message, taille, tamponDecodage);
    if(typeAttendu == tamponDecodage[0])
    {
        return (void*)tamponDecodage;
    }
    return NULL;
}
