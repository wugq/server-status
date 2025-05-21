#include <Arduino.h>

void setup() {
    Serial1.begin(9600);
    // Serial1.write("hi");
    // Serial1.println("hi");
    // Serial1.flush();
    Serial.begin(9600);
}

String readSerialCommand() {
    String command = "";

    while (Serial1.available() > 0) {
        // Serial.println("Command received");
        command = Serial1.readStringUntil('\n');
        // command += Serial1.read();
        // char c = Serial1.read();

        // if (c == '\n') {
        // return command;
        // } else {
        // command += c;
        // }
        // if (const char c = Serial1.read()  c == '\n') {
        //     Serial.println("Command received");
        //     return command;
        // } else {
        //     command += c;
        // }

        // Small delay to allow buffer to fill
        // delay(2);
    }
    return command;

    // return ""; // Return an empty string if no complete command
}

void loop() {
    const String command = readSerialCommand();

    // Serial.print("Command received: ");
    // Serial.println(command);
    if (command.length() > 1) {
        Serial.print("Command received---: ");
        Serial.println(command);
        //     // Process the command here
    }
}
