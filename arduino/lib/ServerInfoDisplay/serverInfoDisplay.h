#pragma once
#include "button.h"
#include "serverInfo.h"
#include "displayFourBitLed.h"
#include "serverInfoDisplay.h"

#ifndef SERVERINFODISPLAY_H
#define SERVERINFODISPLAY_H

#endif //SERVERINFODISPLAY_H

constexpr int IPADDRESS_SIZE = 16;

typedef struct {
    unsigned int index;
    char *message;
    unsigned int length;
} serverInfoDisplayData;

void serverInfoDisplaySetMessage(serverInfoDisplayData *srvInfoDisplayData,
                                 const serverInfoData *srvInfoData,
                                 const buttonState *btnState);

void serverInfoDisplaySetDisplay(serverInfoDisplayData *srvInfoDisplayData,
                                 const displayFourBitLedConfig *displayFourBitLedConfig);
