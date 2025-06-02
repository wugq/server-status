#include <cstring>
#include <api/itoa.h>

#include "serverInfoDisplay.h"


void setCPUInfo(serverInfoDisplayData *srvInfoDisplayData, const int cpuLoad) {
    char message[5] = "CP";
    char cpuLoadStr[3];
    const int theCpuLoad = cpuLoad > 100 ? 99 : cpuLoad;
    itoa(theCpuLoad, cpuLoadStr, 10);

    char theCpuLoadStr[3];
    if (theCpuLoad < 10) {
        strcpy(theCpuLoadStr, "0");
        strcat(theCpuLoadStr, cpuLoadStr);
    } else {
        strcpy(theCpuLoadStr, cpuLoadStr);
    }

    strcat(message, theCpuLoadStr);
    strcpy(srvInfoDisplayData->message, message);
    srvInfoDisplayData->length = strlen(srvInfoDisplayData->message);
}

void setIpAddrInfo(serverInfoDisplayData *srvInfoDisplayData, const char *ipAddress) {
    char message[IPADDRESS_DATA_SIZE + 2] = "IP";
    strcat(message, ipAddress);
    strcpy(srvInfoDisplayData->message, message);
    srvInfoDisplayData->length = strlen(srvInfoDisplayData->message);
}

void serverInfoDisplaySetMessage(serverInfoDisplayData *srvInfoDisplayData,
                                 const serverInfoData *srvInfoData,
                                 const buttonState *btnState) {
    srvInfoDisplayData->index = 0;

    switch (btnState->pressedCount % srvInfoData->functionCount) {
        case 0:
            setCPUInfo(srvInfoDisplayData, srvInfoData->cpuLoad);
            break;
        case 1:
            setIpAddrInfo(srvInfoDisplayData, srvInfoData->ipAddress);
            break;
        case 2:
            strcpy(srvInfoDisplayData->message, "Hi");
            break;
        default:
            break;
    }
}

void serverInfoDisplaySetDisplay(serverInfoDisplayData *srvInfoDisplayData,
                                 const displayFourBitLedConfig *displayFourBitLedConfig) {
    const uint8_t count = displayFourBitLedSetString(displayFourBitLedConfig,
                                                     srvInfoDisplayData->message + srvInfoDisplayData->index);
    if (count < 4) {
        srvInfoDisplayData->index = 0;
    } else {
        srvInfoDisplayData->index += count;
    }

    if (srvInfoDisplayData->index >= srvInfoDisplayData->length) {
        srvInfoDisplayData->index = 0;
    }
}
