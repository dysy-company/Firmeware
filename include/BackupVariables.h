#ifndef BACKUP_VARIABLES_H
#define BACKUP_VARIABLES_H

#include <mbed.h>
#include "..//..//include//Boards//Board.h"

typedef struct backupVariables{
    int32_t *valvePosition;
    int32_t *encoderPulses;
    double *strainNullOffset;
} backupVariables_t;
#endif