
#ifndef SERVERINFO_H
#define SERVERINFO_H

#endif //SERVERINFO_H

typedef struct {
    int cpuLoad;
    int ipAddress;
} serverInfoData;

void serverInfoSet(serverInfoData *srvInfoData, const serverInfoData *newInfo);
