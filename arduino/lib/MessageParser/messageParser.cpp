#include "messageParser.h"

#include <Arduino.h>
#include <cstring>

#include "serverInfoDisplay.h"

void printHeader(const char *header, const int length) {
    const int space = (length - strlen(header) - 2) / 2;
    for (int i = 0; i < space; i++) {
        Serial.print("*");
    }
    Serial.print(" ");
    Serial.print(header);
    Serial.print(" ");
    for (int i = 0; i < space; i++) {
        Serial.print("*");
    }
    Serial.println();
}

void printMessage(const messageParserBuffer *msgParserBuffer) {
    printHeader("Message", 30);
    for (int i = 0; i < msgParserBuffer->currentIndex; i++) {
        Serial.print(i);
        Serial.print(" -> ");
        Serial.print(msgParserBuffer->message[i]);
        Serial.println();
    }
    Serial.println();
}

bool checkMessage(const messageParserBuffer *msgParserBuffer) {
    printHeader("Check Message", 30);
    if (msgParserBuffer->message[1] != msgParserBuffer->currentIndex) {
        Serial.println("Message is not completed\n");
        return false;
    }
    if (msgParserBuffer->message[0] != '<' ||
        msgParserBuffer->message[msgParserBuffer->currentIndex - 1] != '>') {
        Serial.println("Message is not completed\n");
        return false;
    }
    Serial.println("Check Message finished\n");
    return true;
}

void resetBuffer(messageParserBuffer *msgParserBuffer) {
    msgParserBuffer->currentIndex = 0;
    msgParserBuffer->cpuLoadStart = 0;
    msgParserBuffer->cpuLoadEnd = 0;
    msgParserBuffer->ipAddressStart = 0;
    msgParserBuffer->ipAddressEnd = 0;
    memset(msgParserBuffer->message, 0, sizeof(msgParserBuffer->message));
}


void findServerInfoData(const messageParserBuffer *msgParserBuffer,
                        const char type,
                        uint8_t *startPtr,
                        uint8_t *endPtr) {
    bool isFound = false;
    for (int i = 0; i < msgParserBuffer->currentIndex; i++) {
        if (msgParserBuffer->message[i] == '#' && msgParserBuffer->message[i + 1] == type) {
            *startPtr = i + 2;
            isFound = true;
            continue;
        }
        if (isFound && (
                msgParserBuffer->message[i] == '#' ||
                msgParserBuffer->message[i] == '>')
        ) {
            *endPtr = i - 1;
            isFound = false;
        }
    }
}

void setCpuLoad(serverInfoData *srvInfoData, const messageParserBuffer *msgParserBuffer) {
    if (msgParserBuffer->cpuLoadStart == 0 || msgParserBuffer->cpuLoadEnd == 0) {
        return;
    }
    if (msgParserBuffer->cpuLoadEnd < msgParserBuffer->cpuLoadStart) {
        return;
    }
    if (msgParserBuffer->cpuLoadEnd != msgParserBuffer->cpuLoadStart) {
        return;
    }

    srvInfoData->cpuLoad = msgParserBuffer->message[msgParserBuffer->cpuLoadStart];
}

void setIpAddress(serverInfoData *srvInfoData, const messageParserBuffer *msgParserBuffer) {
    if (msgParserBuffer->ipAddressStart == 0 || msgParserBuffer->ipAddressEnd == 0) {
        return;
    }
    if (msgParserBuffer->ipAddressEnd < msgParserBuffer->ipAddressStart) {
        return;
    }

    const uint8_t ipCount = msgParserBuffer->message[msgParserBuffer->ipAddressStart];
    const uint8_t byteCount = ipCount * 4 + 1;
    if (msgParserBuffer->ipAddressEnd - msgParserBuffer->ipAddressStart + 1 != byteCount) {
        Serial.println("IP address is not correct\n");
        return;
    }

    char ipAddressBuffer[IPADDRESS_SIZE * ipCount] = {};
    char *ipAddressBufferPtr = ipAddressBuffer;

    const uint8_t dataLength = msgParserBuffer->ipAddressEnd - msgParserBuffer->ipAddressStart;
    const uint8_t *ipAddressDataPtr = msgParserBuffer->message
                                      + msgParserBuffer->ipAddressStart
                                      + 1;

    char charBuffer[4];
    for (int i = 0; i <= dataLength - 1; i++) {
        snprintf(charBuffer,
                 sizeof(charBuffer),
                 "%d",
                 *ipAddressDataPtr++);
        strcat(ipAddressBufferPtr, charBuffer);

        if ((i + 1) % 4 == 0) {
            if (i != dataLength - 1) {
                strcat(ipAddressBufferPtr, "_");
            }
        } else if (i != dataLength) {
            strcat(ipAddressBufferPtr, ".");
        }
    }

    Serial.println(charBuffer);
    Serial.println(ipAddressBuffer);

    strcpy(srvInfoData->ipAddress, ipAddressBuffer);
}


void setServerInfoData(serverInfoData *srvInfoData, messageParserBuffer *msgParserBuffer) {
    findServerInfoData(msgParserBuffer, 'C', &msgParserBuffer->cpuLoadStart, &msgParserBuffer->cpuLoadEnd);
    findServerInfoData(msgParserBuffer, 'I', &msgParserBuffer->ipAddressStart, &msgParserBuffer->ipAddressEnd);

    setCpuLoad(srvInfoData, msgParserBuffer);
    setIpAddress(srvInfoData, msgParserBuffer);
}


void messageParserDoParse(serverInfoData *srvInfoData, messageParserBuffer *msgParserBuffer, const int incomingData) {
    msgParserBuffer->message[msgParserBuffer->currentIndex++] = incomingData;
    if (incomingData != '>') {
        return;
    }

    printMessage(msgParserBuffer);
    if (checkMessage(msgParserBuffer)) {
        setServerInfoData(srvInfoData, msgParserBuffer);
    }
    resetBuffer(msgParserBuffer);
}
