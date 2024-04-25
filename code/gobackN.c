#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_SEQ 7 // Maximum sequence number
#define TIMEOUT 5 // Timeout in seconds

bool ackReceived[MAX_SEQ + 1]; // Array to track acknowledgments
int base = 0; // Base sequence number
int nextSeqNum = 0; // Next sequence number to send

void sendFrame(int seqNum) {
    printf("Sender: Sending frame %d\n", seqNum);
    // Simulate sending the frame
    ackReceived[seqNum] = false;
}

void receiveAck(int seqNum) {
    printf("Receiver: Receiving Acknowledgement for frame %d\n", seqNum);
    ackReceived[seqNum] = true;
}

void resendFrames() {
    printf("Timeout: Resending frames from %d\n", base);
    for (int i = base; i <= nextSeqNum; i++) {
        if (!ackReceived[i]) {
            sendFrame(i);
        }
    }
}

void waitForEvent() {
    sleep(1); // Simulate waiting for an event
}

int main() {
    bool isSender = true;

    while (true) {
        if (waitForEvent()) {
            if (isSender) {
                if (nextSeqNum <= MAX_SEQ) {
                    sendFrame(nextSeqNum);
                    nextSeqNum++;
                }

                // Simulate receiving an acknowledgment
                receiveAck(nextSeqNum - 1);

                // Check if all frames have been acknowledged
                if (ackReceived[base]) {
                    base++;
                }
            } else {
                // Simulate receiving a frame
                receiveAck(nextSeqNum - 1);
                isSender = !isSender; // Switch roles
            }
        }
    }

    return 0;
}
