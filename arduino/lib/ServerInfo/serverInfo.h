#pragma once

#ifndef SERVERINFO_H
#define SERVERINFO_H

#endif //SERVERINFO_H

typedef struct {
    int functionCount;
    int cpuLoad;
    char *ipAddress;
} serverInfoData;


void serverInfoInit(serverInfoData *srvInfoData);

void serverInfoSet(serverInfoData *srvInfoData, const serverInfoData *newInfo);
