#pragma once

#ifndef MESSAGEREPLY_H
#define MESSAGEREPLY_H
#include <cstdint>

#endif //MESSAGEREPLY_H

typedef struct {
    uint8_t *message;
    uint8_t isReady;
} messageReplyData;

void sendReply(messageReplyData *replyData);
