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
    memset(msgParserBuffer->message, 0, sizeof(msgParserBuffer->message));
}


void setServerInfoData(serverInfoData *srvInfoData, messageParserBuffer *msgParserBuffer) {
    Serial.println("setServerInfoData");
}


void messageParserDoParse(serverInfoData *srvInfoData, messageParserBuffer *msgParserBuffer, const int incomingData) {
    msgParserBuffer->message[msgParserBuffer->currentIndex++] = incomingData;
    if (incomingData == '>') {
        printMessage(msgParserBuffer);
        if (checkMessage(msgParserBuffer)) {
            setServerInfoData(srvInfoData, msgParserBuffer);
        }

        resetBuffer(msgParserBuffer);
    }
}
