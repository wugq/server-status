#pragma once
#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H
#include <api/Common.h>

#include "serverInfo.h"

#endif //MESSAGEPARSER_H

constexpr int MESSAGE_PARSER_BUFFER_SIZE = 200;
typedef struct {
    uint8_t *message;
    uint8_t currentIndex;
} messageParserBuffer;

/**
 * Parses the provided message and extracts server information into the given serverInfoData structure.
 *
 * @param srvInfoData A pointer to the serverInfoData structure where the extracted data will be stored.
 * @param msgParserBuffer The messageParserBuffer structure that contains the message to be parsed.
 * @param incomingData New Byte from serial
 */
void messageParserDoParse(serverInfoData *srvInfoData, messageParserBuffer *msgParserBuffer, const int incomingData);
