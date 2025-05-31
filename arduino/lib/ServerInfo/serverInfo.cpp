#include "serverInfo.h"

void printCPU() {
}

void printIP() {
}

void print(int index) {
    int idx = index % 2;

    if (idx == 0) {
        printCPU();
    } else {
        printIP();
    }
}

void serverInfoSet(serverInfoData *srvInfoData, const serverInfoData *newInfo) {
    srvInfoData->cpuLoad = newInfo->cpuLoad;
    srvInfoData->ipAddress = newInfo->ipAddress;
}
