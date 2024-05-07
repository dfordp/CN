#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

bool ackReceived = false;

void sendFrame() {
    printf("Sender: Sending frame\n");
}

void receiveFrame() {
    printf("Receiver: Receiving frame\n");
}

void sendAck() {
    printf("Receiver: Sending Acknowledgement\n");
}

void receiveAck() {
    printf("Sender: Receiving Acknowledgement\n");
    ackReceived = true;
}

bool waitForEvent() {
    sleep(1);
    return true;
}

int main() {
    bool isSender = true;

    while (true) {
        if (waitForEvent()) {
            if (isSender) {
                sendFrame();
                if (!ackReceived) {
                    printf("Timeout: Resending frame\n");
                    sendFrame();
                }
                receiveAck();
            } else {
                receiveFrame();
                sendAck();
                isSender = !isSender; // Only switch to sender after receiving Ack
            }
        }
    }

    return 0;
}
