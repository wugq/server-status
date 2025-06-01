#include "serverInfo.h"

#include <cstring>

void serverInfoInit(serverInfoData *srvInfoData) {
    srvInfoData->functionCount = 2;
    srvInfoData->cpuLoad = 0;
    strcpy(srvInfoData->ipAddress, "192.168.0.123");
}

void serverInfoSet(serverInfoData *srvInfoData, const serverInfoData *newInfo) {
    srvInfoData->cpuLoad = newInfo->cpuLoad;
    strcpy(srvInfoData->ipAddress, newInfo->ipAddress);
}
