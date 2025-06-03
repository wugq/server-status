#include "serverInfo.h"

#include <cstring>

// ============= public methods =============
void serverInfoInit(serverInfoData *srvInfoData) {
    srvInfoData->functionCount = 2;
    srvInfoData->cpuLoad = 0;
    strcpy(srvInfoData->ipAddress, "0.0.0.0");
}

void serverInfoSet(serverInfoData *srvInfoData, const serverInfoData *newInfo) {
    srvInfoData->cpuLoad = newInfo->cpuLoad;
    strcpy(srvInfoData->ipAddress, newInfo->ipAddress);
}
