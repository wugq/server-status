#include "messageReply.h"

#include <Arduino.h>

void sendReply(messageReplyData *replyData) {
    constexpr char message[10] = "message";

    Serial1.write(message, 10);
}

// void setReplyMessage(messageReplyData *replyData, const char *message);
